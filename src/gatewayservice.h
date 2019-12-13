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
    Heartbeat *_heartbeat;
    QWebSocket *_socket;
    QTimer *_heartbeatTimer;
    QUrl m_url;

    bool _debug = true;
    bool _heartbeatAck = false;
    int _lastSequenceNumber = -1;

    void processHello(QSharedPointer<GatewayPayload> payload);
    void processPayload(QSharedPointer<GatewayPayload> payload);
    void sendHeartbeat();
};

#endif // GATEWAYCONNECTION_H
