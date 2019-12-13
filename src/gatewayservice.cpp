#include "gatewayservice.h"
#include "jsonserializer.h"
#include "globals.h"
#include "payloads/hello.h"

#include <QSettings>
#include <QThread>



GatewayService::GatewayService(const QUrl& url, QObject *parent) :
    QObject(parent),
    m_url(url)
{    

}

GatewayService::~GatewayService() {
    _socket->close();
    delete _socket;

    _heartbeatTimer->stop();
    delete _heartbeatTimer;
    delete _heartbeat;
}

void
GatewayService::init() {
    if (_debug)
        qDebug() << "Gateway Connection Url: " << m_url.toString();

    _socket = new QWebSocket;

    connect(_socket, &QWebSocket::connected, this, [&](){
        qDebug() << "WebSocket connected";
        QString str("{ \"op\" : 10, \"d\" : { \"heartbeat_interval\" : 5000 } }");
        _socket->sendTextMessage(str);
    });

    connect(_socket, &QWebSocket::textMessageReceived, this, [&](QString messageString) {
        qDebug() << "Message recieved: " << messageString;
        QSharedPointer<GatewayPayload> event(new GatewayPayload);
        JsonSerializer::fromQString(*event, messageString);
        processPayload(event);
    });

    connect(_socket, &QWebSocket::binaryMessageReceived, this, [&](QByteArray messageArray){
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
    _heartbeat = new Heartbeat;
    connect(_heartbeatTimer, &QTimer::timeout, this, &GatewayService::sendHeartbeat);

    _socket->open(QUrl(m_url));
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
            _heartbeatAck = true;
            break;
        default:
            emit payloadReady(payload);
            break;
    }
}

void
GatewayService::sendTextMessage(const JsonSerializeable &message) {
    _socket->sendTextMessage(JsonSerializer::toQString(message));
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
    _heartbeat->setD(_lastSequenceNumber);
    _socket->sendTextMessage(JsonSerializer::toQString(*_heartbeat));
    _heartbeatAck = false;
}
