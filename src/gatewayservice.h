#ifndef GATEWAYCONNECTION_H
#define GATEWAYCONNECTION_H

#include <QObject>
#include <QTimer>
#include <QtWebSockets/QWebSocket>

#include "payloads/heartbeat.h"
#include "payloads/gatewaypayload.h"


class GatewayService : public QObject
{
    Q_OBJECT

public:
    GatewayService(const QUrl &url, QObject *parent = nullptr);
    ~GatewayService();

public slots:
    void init();
    void sendTextMessage(const JsonSerializeable &message);
    void sendBinaryMessage(const JsonSerializeable &message);

Q_SIGNALS:
    void payloadReady(QSharedPointer<GatewayPayload> payload);

private:
    Heartbeat *m_heartBeat;
    QWebSocket *m_socket;
    QTimer *m_heartbeatTimer;
    QUrl m_url;

    bool m_debug = true;
    bool m_heartbeatAck = false;
    int m_lastSequenceNumber = -1;

    void processHello(QSharedPointer<GatewayPayload> payload);
    void processPayload(QSharedPointer<GatewayPayload> payload);
    void sendHeartbeat();
};

#endif // GATEWAYCONNECTION_H
