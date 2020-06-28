#include "echoserver.h"
#include "payloads/gatewaypayload.h"
#include "globals.h"
#include "jsonutils.h"
#include "payloads/hello.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
EchoServer::EchoServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &EchoServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &EchoServer::closed);
    }

}
//! [constructor]

EchoServer::~EchoServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

//! [onNewConnection]
void EchoServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &EchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &EchoServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);

    m_clients << pSocket;

    Hello hello;
    hello.setHeartbeatInterval(5000);

    GatewayPayload::GatewayPayload payload;
    payload.d = JsonUtils::toQJsonObject(hello);
    payload.op = GatewayEvents::HELLO;

    pSocket->sendTextMessage(payload.toQString());
}
//! [onNewConnection]

//! [processTextMessage]
void EchoServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    GatewayPayload::GatewayPayload payload;
    payload.fromQString(message);

    qDebug() << "Message received:" << message;

    GatewayPayload::GatewayPayload out;
    if (pClient) {
        switch (payload.op) {
            case GatewayEvents::HEARTBEAT:
                out.op = GatewayEvents::HEARTBEAT_ACK;
                out.s = s++;
                break;
        }
        QString outString = out.toQString();
        qDebug().noquote() << "sent: " + outString;
        pClient->sendTextMessage(outString);
    }
}
//! [processTextMessage]

//! [processBinaryMessage]
void EchoServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void EchoServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]
