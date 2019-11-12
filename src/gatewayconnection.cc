#include "gatewayconnection.h"
#include "jsonserializer.h"
#include <stack>
#include <regex>
#include <memory>
#include <QStack>


GatewayConnection::GatewayConnection(const QUrl& url, QObject *parent) :
    QObject(parent),
    url_(url)
{
    if (debug_)
        qDebug() << "Gateway Connection Url: " << url.toString();
    connect(&socket_, &QWebSocket::connected, this, &GatewayConnection::onConnected);
    connect(&socket_, &QWebSocket::textMessageReceived, this, &GatewayConnection::onTextMessageReceived);
    connect(&socket_, &QWebSocket::binaryMessageReceived, this, &GatewayConnection::onBinaryMessageReceived);
    connect(&socket_, &QWebSocket::disconnected, this, &GatewayConnection::reconnect);
    socket_.open(QUrl(url));
}

void
GatewayConnection::onConnected() {

    //do nothing, wait for OPCODE 10 for now and dispatch accordingly
}

void
GatewayConnection::reconnect() {
    //TODO implement reco
}

void
GatewayConnection::onTextMessageReceived(QString message) {
    GatewayPayload payload;
    JsonSerializer::fromQString(message, payload);
    emit payloadReady(payload);
}

void
GatewayConnection::onBinaryMessageReceived(QByteArray message) {
    GatewayPayload payload;
    JsonSerializer::fromByteArray(message, payload);
    emit payloadReady(payload);
}
