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

    enum GatewayCloseCodes {
        UNKNOWN_ERROR = 4000,
        UNKNOWN_OPCODE = 4001,
        DECODE_ERROR = 4002,
        NOT_AUTHENTICATED = 4003,
        AUTHENTICATION_FAILED = 4004,
        ALREADY_AUTHENTICATED = 4005,
        INVALID_SEQ = 4007,
        RATE_LIMITED = 4008,
        SESSION_TIMED_OUT = 4009,
        INVALID_SHARD = 40010,
        SHARDING_REQUIRED = 4011,
        INVALID_API_VERSION = 4012,
        INVALID_INTENTS = 4013,
        DISALLOWED_INTENTS = 4014
    };

    enum GatewayIntents {
        GUILDS = 0,
        GUILD_MEMBERS = 1,
        GUILD_BANS = 2,
        GUILD_EMOJIS = 3,
        GUILD_INTEGRATIONS = 4,
        GUILD_WEBHOOKS = 5,
        GUILD_INVITES = 6,
        GUILD_VOICE_STATES = 7,
        GUILD_PRESENCES = 8,
        GUILD_MESSAGES = 9,
        GUILD_MESSAGE_REACTIONS = 10,
        GUILD_MESSAGE_TYPING = 11,
        DIRECT_MESSAGES = 12,
        DIRECT_MESSAGE_REACTIONS = 13,
        DIRECT_MESSAGE_TYPING = 14
    };

    void init();

public slots:
    void sendTextMessage(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void sendBinaryMessage(QSharedPointer<GatewayPayload::GatewayPayload> payload);

Q_SIGNALS:
    void dispatchEvent(QSharedPointer<GatewayPayload::GatewayPayload> payload);

private:
    QSharedPointer<QWebSocket> _socket;
    QSharedPointer<QTimer> _heartbeatTimer;

    Heartbeat _heartbeat;
    Logger* _logger;
    bool _heartbeatAck;
    bool _resume;
    int _lastSequenceNumber;    
    QUrl _gateway;
    QString _botToken;
    QString _sessionId;

    void attemptReconnect(int closeCode);
    QUrl buildConnectionUrl(QSharedPointer<Settings> settings);
    void processAck();
    void processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processHello(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processInvalidSession(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processPayload(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processReady(QSharedPointer<GatewayPayload::GatewayPayload> payload);
    void processReconnect();
    void onBinaryMessageReceived(QByteArray messageArray);
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void reconnect(int sleep);
    void sendHeartbeat();
    void sendIdentify();
    void sendResume();
    void sendTextPayload(QString payload);

    Q_ENUM(GatewayCloseCodes)
};

#endif // GATEWAYCONNECTION_H
