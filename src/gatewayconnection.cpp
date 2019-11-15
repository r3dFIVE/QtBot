#include "gatewayconnection.h"
#include "jsonserializer.h"

#include <QThread>

GatewayConnection::GatewayConnection(const QUrl& url, QObject *parent) :
    QObject(parent),
    _url(url)
{    

}

GatewayConnection::~GatewayConnection() {
    _socket->close();
}

void
GatewayConnection::init() {
    if (_debug)
        qDebug() << "Gateway Connection Url: " << _url.toString();

    _socket = new QWebSocket;

    connect(_socket, &QWebSocket::connected, this, &GatewayConnection::onConnected);
    connect(_socket, &QWebSocket::textMessageReceived, this, &GatewayConnection::onTextMessageReceived);
    connect(_socket, &QWebSocket::binaryMessageReceived, this, &GatewayConnection::onBinaryMessageReceived);
    connect(_socket, &QWebSocket::disconnected, this, &GatewayConnection::reconnect);
    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
        [=](QAbstractSocket::SocketError error) {
            qDebug() << error;
        }
    );

    _socket->open(QUrl(_url));
}

void
GatewayConnection::onConnected() {
    qDebug() << "WebSocket connected";
    QString str("{ \"op\" : 10, \"d\" : { \"heartbeat_interval\" : 5000 } }");
    _socket->sendTextMessage(str);
    //do nothing, wait for OPCODE 10 for now and dispatch accordingly
}

void
GatewayConnection::reconnect() {
    //TODO implement reco
}

void
GatewayConnection::onTextMessageReceived(QString message) {
    qDebug() << "Message recieved: " << message;
    GatewayPayload payload;
    JsonSerializer::fromQString(payload, message);
    emit payloadReady(123);
}

void
GatewayConnection::onBinaryMessageReceived(QByteArray message) {
    GatewayPayload payload;
    JsonSerializer::fromByteArray(payload, message);
    emit payloadReady(123);
}

void
GatewayConnection::sendTextMessage(const JsonSerializeable &message) {
    _socket->sendTextMessage(JsonSerializer::toQString(message));
}

void
GatewayConnection::sendBinaryMessage(const JsonSerializeable &message) {
    _socket->sendBinaryMessage(JsonSerializer::toByteArray(message));
}

void
GatewayConnection::updateHeartbeatInterval(int heartbeatInterval) {
    _heartbeatInterval = heartbeatInterval;
}
