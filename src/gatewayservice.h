#ifndef GATEWAYCONNECTION_H
#define GATEWAYCONNECTION_H

#include <QObject>
#include <QTimer>
#include <QtWebSockets/QWebSocket>
#include <QSharedPointer>

#include "payloads/heartbeat.h"
#include "payloads/gatewaypayload.h"
#include "settingsservice.h"
#include "loggingservice.h"


class GatewayService : public QObject
{
    Q_OBJECT

public:
    GatewayService(QSharedPointer<SettingsService> settings, QObject *parent = nullptr);
    ~GatewayService();

public slots:
    void init();
    void sendTextMessage(const JsonSerializeable &message);
    void sendBinaryMessage(const JsonSerializeable &message);

Q_SIGNALS:
    void eventReady(QSharedPointer<GatewayPayload> payload);

private:
    QWebSocket *_socket;
    QTimer *_heartbeatTimer;

    Heartbeat _heartbeat;
    Logger _logger;
    bool _heartbeatAck;
    int _lastSequenceNumber;
    QSharedPointer<SettingsService> _settings;

    QUrl buildConnectionUrl();
    void processHello(QSharedPointer<GatewayPayload> payload);
    void processPayload(QSharedPointer<GatewayPayload> payload);
    void sendHeartbeat();
};

#endif // GATEWAYCONNECTION_H
