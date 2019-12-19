#include "gatewayservice.h"
#include "jsonserializer.h"
#include "globals.h"
#include "payloads/hello.h"

#include <QSettings>
#include <QThread>

GatewayService::GatewayService(QSharedPointer<SettingsService> settings, QObject *parent) :
    QObject(parent),
    _settings(settings)
{    
    _lastSequenceNumber = -1;
    _heartbeatAck = false;
    _logger = LoggingService::getLogger();
}

GatewayService::~GatewayService() {
    _socket->close();
    delete _socket;

    _heartbeatTimer->stop();
    delete _heartbeatTimer;
}

void
GatewayService::init() {
    QUrl connectionUrl = buildConnectionUrl();
    _logger->debug("Gateway Connection Url: " + connectionUrl.toString().toStdString());

    _socket = new QWebSocket;

    connect(_socket, &QWebSocket::connected, this, [&](){
        _logger->info("Gateway connection established.");
    });

    connect(_socket, &QWebSocket::textMessageReceived, this, [&](QString messageString) {
        _logger->trace("Message recieved: " + messageString.toStdString());
        QSharedPointer<GatewayPayload> event(new GatewayPayload);
        JsonSerializer::fromQString(*event, messageString);
        processPayload(event);
    });

    connect(_socket, &QWebSocket::binaryMessageReceived, this, [&](QByteArray messageArray){
        _logger->trace("Message recieved: " + messageArray.toStdString());
        QSharedPointer<GatewayPayload> event(new GatewayPayload);
        JsonSerializer::fromByteArray(*event, messageArray);
        processPayload(event);
    });

    connect(_socket, &QWebSocket::disconnected, this,
            [&](){
        // Disconnect not implemented
    });

    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
        [=](QAbstractSocket::SocketError error) {
            qDebug() << error;
        }
    );

    _heartbeatTimer = new QTimer(this);
    connect(_heartbeatTimer, &QTimer::timeout, this, &GatewayService::sendHeartbeat);

    _socket->open(QUrl(connectionUrl));
}


void
GatewayService::processPayload(QSharedPointer<GatewayPayload> payload) {
    _lastSequenceNumber = payload->s();

    switch(payload->op()) {
        case GatewayOpcodes::HELLO:
            processHello(payload);
            break;
        case GatewayOpcodes::HEARTBEAT:
            //sendHeartbeat();
            break;
        case GatewayOpcodes::HEARTBEAT_ACK:
            break;
        default:
            emit eventReady(payload);
            break;
    }
}

void
GatewayService::processAck() {
    _logger->trace(QString("ACK receieved for sequence number: %1").arg(_lastSequenceNumber).toStdString());

    _heartbeatAck = true;

}

void
GatewayService::sendTextMessage(const JsonSerializeable &message) {
    QString messageStr = JsonSerializer::toQString(message);
    _socket->sendTextMessage(messageStr);
    _logger->trace("Sent gateway message: " + messageStr.toStdString());
}

void
GatewayService::sendBinaryMessage(const JsonSerializeable &message) {
    _socket->sendBinaryMessage(JsonSerializer::toByteArray(message));
}

void
GatewayService::processHello(QSharedPointer<GatewayPayload> payload) {
    Hello helloEvent;
    JsonSerializer::fromQJsonObject(helloEvent, payload->d());

    if (_heartbeatTimer->isActive()) {
        _heartbeatTimer->stop();
    }

    _heartbeatTimer->setInterval(helloEvent.heartbeatInterval());
    _heartbeatTimer->start();
}

void
GatewayService::sendHeartbeat() {    
    _heartbeat.setD(_lastSequenceNumber);
    _socket->sendTextMessage(JsonSerializer::toQString(_heartbeat));
    _heartbeatAck = false;
    _logger->trace("Heartbeat sent: " + JsonSerializer::toQString(_heartbeat).toStdString());
}


QUrl
GatewayService::buildConnectionUrl() {
    QString zlibParameter = "";
    if (_settings->value(Settings::Connection::ZLIB_ENABLED).toBool()) {
        zlibParameter = "&compress=zlib-stream";
    }

    QString baseUrl = _settings->value(Settings::Connection::CONNECTION_URL).toString();
    QString fullUrl = QString("%1/?v=6&encoding=json%2").arg(baseUrl).arg(zlibParameter);

    return QUrl(fullUrl);
}

