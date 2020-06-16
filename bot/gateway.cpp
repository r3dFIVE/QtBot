#include "gateway.h"
#include "globals.h"
#include "payloads/hello.h"
#include "logging/logfactory.h"

#include <QSettings>
#include <QThread>

#include "payloads/resume.h"
#include "payloads/identify.h"

Gateway::Gateway(QSharedPointer<Settings> settings, QObject *parent) :
    QObject(parent)
{    
    _lastSequenceNumber = -1;
    _heartbeatAck = false;
    _resume = false;
    _logger = LogFactory::getLogger();
    _baseUrl = settings->value(SettingsParam::Connection::CONNECTION_URL).toString();
    _zlibEnabled = settings->value(SettingsParam::Connection::ZLIB_ENABLED).toBool();
}

Gateway::~Gateway() {
    _socket->close();
    delete _socket;

    _heartbeatTimer->stop();
    delete _heartbeatTimer;
}

void
Gateway::init() {
    QUrl connectionUrl = buildConnectionUrl();
    _logger->debug("Gateway Connection Url: " + connectionUrl.toString());

    _socket = new QWebSocket;

    connect(_socket, &QWebSocket::connected, this, [&](){
        _logger->info("Gateway connection established.");
    });

    connect(_socket, &QWebSocket::textMessageReceived, this, [&](QString messageString) {
        _logger->trace("Message recieved: " + messageString);
        QSharedPointer<GatewayPayload> event(new GatewayPayload);
        event->fromQString(messageString);
        processPayload(event);
    });

    connect(_socket, &QWebSocket::binaryMessageReceived, this, [&](QByteArray messageArray){
        _logger->trace("Message recieved: " + messageArray);
        QSharedPointer<GatewayPayload> event(new GatewayPayload);
        event->fromByteArray(messageArray);
        processPayload(event);
    });

    connect(_socket, &QWebSocket::disconnected, this, [&](){
        // Disconnect not implemented
    });

    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
        [=](QAbstractSocket::SocketError error) {
            _logger->critical(QString("QSocketError: %1").arg(error));
        }
    );

    _heartbeatTimer = new QTimer(this);
    connect(_heartbeatTimer, &QTimer::timeout, this, &Gateway::sendHeartbeat);

    _socket->open(QUrl(connectionUrl));
}

//bool
//GatewayService::attemptReconnect() {

//}


void
Gateway::processPayload(QSharedPointer<GatewayPayload> payload) {
    switch(payload->op) {
        case GatewayOpcodes::HELLO:
            processHello(payload);
            break;
        case GatewayOpcodes::HEARTBEAT:
            sendHeartbeat();
            break;
        case GatewayOpcodes::HEARTBEAT_ACK:
            processAck();
            break;
        case GatewayOpcodes::DISPATCH:
            processDispatch(payload);
            break;
    }
}

void
Gateway::processDispatch(QSharedPointer<GatewayPayload> payload) {
    _lastSequenceNumber = payload->s;

    if (payload->t == GatewayEvents::READY) {
        processReady(payload);
    }

    emit dispatchEvent(payload);
}

void
Gateway::processReady(QSharedPointer<GatewayPayload> payload) {
    //Ready ready;

}

void
Gateway::processAck() {
    _logger->trace(QString("ACK receieved for sequence number: %1").arg(_lastSequenceNumber));
    _heartbeatAck = true;
}

void
Gateway::sendTextMessage(QSharedPointer<GatewayPayload> payload) {
    QString messageStr = payload->toQString();
    _socket->sendTextMessage(messageStr);
    _logger->trace("Sent gateway payload: " + messageStr);
}

void
Gateway::sendBinaryMessage(QSharedPointer<GatewayPayload> payload) {
    _socket->sendBinaryMessage(payload->toByteArray());
}

void
Gateway::processHello(QSharedPointer<GatewayPayload> payload) {
    Hello helloEvent;
    helloEvent.read(payload->d);

    if (_heartbeatTimer->isActive()) {
        _heartbeatTimer->stop();
    }

    _heartbeatTimer->setInterval(helloEvent.heartbeatInterval);
    _heartbeatTimer->start();

    if (_resume) {
        sendResume();
    } else {
        sendIdentify();
    }
}

void
Gateway::sendIdentify() {
    GatewayPayload payload;
    Identify identify;
}

void
Gateway::sendResume() {    
    Resume resume;
    resume.token = _botToken;
    resume.session_id = _sessionId;
    resume.seq = _lastSequenceNumber;

    GatewayPayload payload;
    payload.op = GatewayOpcodes::RESUME;
    resume.write(payload.d);

    QString payloadString = payload.toQString();
    _socket->sendTextMessage(payloadString);
    _logger->trace("Resume payload sent: " + payloadString);
}

void
Gateway::sendHeartbeat() {
    if (_heartbeatAck == false) {
        _logger->warning("No Heartbeat ack received from previous heartbeat, attemping to reconnect...");
        //TODO handle reconnect
    }

    if (_lastSequenceNumber == -1) {
        _heartbeat.d = NULL;
    }
    _heartbeat.d = _lastSequenceNumber;

    QString payloadString = _heartbeat.toQString();
    _socket->sendTextMessage(payloadString);
    _logger->trace("Heartbeat payload sent: " + payloadString);

    _heartbeatAck = false;
}


QUrl
Gateway::buildConnectionUrl() {
    QString zlibParameter = "";
    if (_zlibEnabled) {
        zlibParameter = "&compress=zlib-stream";
    }

    QString fullUrl = QString("%1/?v=6&encoding=json%2").arg(_baseUrl).arg(zlibParameter);

    return QUrl(fullUrl);
}

