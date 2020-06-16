#ifndef GATEWAYCONNECTION_H
#define GATEWAYCONNECTION_H

#include <QObject>
#include <QTimer>
#include <QtWebSockets/QWebSocket>
#include <QSharedPointer>

#include "payloads/heartbeat.h"
#include "payloads/gatewaypayload.h"
#include "logging/logfactory.h"
#include "settings.h"


class Gateway : public QObject
{
    Q_OBJECT

public:
    Gateway(QSharedPointer<Settings> settings, QObject *parent = nullptr);
    ~Gateway();

    void init();

public slots:
    void sendTextMessage(QSharedPointer<GatewayPayload> payload);
    void sendBinaryMessage(QSharedPointer<GatewayPayload> payload);

Q_SIGNALS:
    void dispatchEvent(QSharedPointer<GatewayPayload> payload);

private:
    QWebSocket *_socket;
    QTimer *_heartbeatTimer;

    Heartbeat _heartbeat;
    Logger* _logger;
    bool _heartbeatAck;
    bool _resume;
    bool _zlibEnabled;
    int _lastSequenceNumber;    
    QString _baseUrl;
    QString _botToken;
    QString _sessionId;

    bool attempReconnect();
    QUrl buildConnectionUrl();
    void processAck();
    void processDispatch(QSharedPointer<GatewayPayload> payload);
    void processHello(QSharedPointer<GatewayPayload> payload);
    void processPayload(QSharedPointer<GatewayPayload> payload);
    void processReady(QSharedPointer<GatewayPayload> payload);
    void sendHeartbeat();
    void sendIdentify();
    void sendResume();
};

#endif // GATEWAYCONNECTION_H
