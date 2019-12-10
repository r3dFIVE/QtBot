#include "gatewayservice.h"
#include "jsonserializer.h"
#include "opcodes/gatewayopcodes.h"

#include <QSettings>
#include <QThread>

#include <src/payloads/hello.h>

GatewayService::GatewayService(const QUrl& url, QObject *parent) :
    QObject(parent),
    m_url(url)
{    

}

GatewayService::~GatewayService() {
    m_socket->close();
    delete m_socket;

    m_heartbeatTimer->stop();
    delete m_heartbeatTimer;
    delete m_heartBeat;
}

void
GatewayService::init() {
    if (m_debug)
        qDebug() << "Gateway Connection Url: " << m_url.toString();

    m_socket = new QWebSocket;

    connect(m_socket, &QWebSocket::connected, this, [&](){
        qDebug() << "WebSocket connected";
        QString str("{ \"op\" : 10, \"d\" : { \"heartbeat_interval\" : 5000 } }");
        m_socket->sendTextMessage(str);
    });

    connect(m_socket, &QWebSocket::textMessageReceived, this, [&](QString messageString) {
        qDebug() << "Message recieved: " << messageString;

        QSharedPointer<GatewayPayload> event(new GatewayPayload);

        JsonSerializer::fromQString(*event, messageString);

        processPayload(event);
    });

    connect(m_socket, &QWebSocket::binaryMessageReceived, this, [&](QByteArray messageArray){
        QSharedPointer<GatewayPayload> event(new GatewayPayload);

        JsonSerializer::fromByteArray(*event, messageArray);

        processPayload(event);
    });

    connect(m_socket, &QWebSocket::disconnected, this,
            [&](){
        // Disconnect not implemented
    });

    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
        [=](QAbstractSocket::SocketError error) {
            qDebug() << error;
        }
    );

    m_heartbeatTimer = new QTimer(this);
    m_heartBeat = new Heartbeat;
    connect(m_heartbeatTimer, &QTimer::timeout, this, &GatewayService::sendHeartbeat);

    m_socket->open(QUrl(m_url));
}


void
GatewayService::processPayload(QSharedPointer<GatewayPayload> payload) {
    m_lastSequenceNumber = payload->s();

    switch(payload->op()) {
        case GatewayOpcodes::HELLO:
            processHello(payload);
            break;
        case GatewayOpcodes::HEARTBEAT:
            //sendHeartbeat();
            break;
        case GatewayOpcodes::HEARTBEAT_ACK:
            m_heartbeatAck = true;
            break;
        default:
            emit payloadReady(payload);
            break;
    }
}

void
GatewayService::sendTextMessage(const JsonSerializeable &message) {
    m_socket->sendTextMessage(JsonSerializer::toQString(message));
}

void
GatewayService::sendBinaryMessage(const JsonSerializeable &message) {
    m_socket->sendBinaryMessage(JsonSerializer::toByteArray(message));
}

void
GatewayService::processHello(QSharedPointer<GatewayPayload> payload) {
    Hello helloEvent;
    JsonSerializer::fromQJsonObject(helloEvent, payload->d());

    if (m_heartbeatTimer->isActive()) {
        m_heartbeatTimer->stop();
    }

    m_heartbeatTimer->setInterval(helloEvent.heartbeatInterval());
    m_heartbeatTimer->start();
}

void
GatewayService::sendHeartbeat() {
    m_heartBeat->setD(m_lastSequenceNumber);
    m_socket->sendTextMessage(JsonSerializer::toQString(*m_heartBeat));
    m_heartbeatAck = false;
}
