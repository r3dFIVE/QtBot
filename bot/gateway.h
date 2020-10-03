#ifndef GATEWAYCONNECTION_H
#define GATEWAYCONNECTION_H

#include <QObject>
#include <QTimer>
#include <QtWebSockets/QWebSocket>
#include <QSharedPointer>

#include "entity/guildentity.h"
#include "payloads/eventcontext.h"
#include "payloads/heartbeat.h"
#include "payloads/gatewaypayload.h"
#include "logging/logfactory.h"
#include "util/settings.h"


class Gateway : public QObject
{
    Q_OBJECT

    QSharedPointer<QWebSocket> _socket;
    QSharedPointer<QTimer> _heartbeatTimer;

    Heartbeat _heartbeat;
    Logger* _logger;
    bool _heartbeatAck = true;
    bool _attemptResume = false;
    int _gatewayIntents = 0;
    int _lastSequenceNumber = -1;
    int _maxRetries;
    int _retryCount;

    QUrl _gatewayUrl;
    QString _botToken;
    QString _sessionId;

    void calculateGatewayIntents(QSharedPointer<Settings> settings);
    void closeConnection(QWebSocketProtocol::CloseCode closeCode);
    void buildConnectionUrl(QSharedPointer<Settings> settings);
    void processAck();
    void processDispatch(QSharedPointer<GatewayPayload> payload);
    void processGuildCreate(QSharedPointer<GatewayPayload> payload);
    void processHello(QSharedPointer<GatewayPayload> payload);
    void processInvalidSession(QSharedPointer<GatewayPayload> payload);
    void processPayload(QSharedPointer<GatewayPayload> payload);
    void processReady(QSharedPointer<GatewayPayload> payload);
    void processReconnect();
    void processResumed(QSharedPointer<GatewayPayload> payload);
    void onBinaryMessageReceived(QByteArray messageArray);
    void onDisconnected();
    void tooManyReconnects();
    void onSocketError(QAbstractSocket::SocketError errorCode);
    void onTextMessageReceived(const QString &message);
    void reconnect(int mSleep);
    void sendHeartbeat();
    void sendIdentify();
    void sendResume();
    void sendTextPayload(const QString &payload);

public:
    Gateway(QSharedPointer<Settings> settings);
    ~Gateway();    

    enum CloseCodes {
        CLOSE_NORMAL = 1000, //Unresumable! Considered a graceful shutdown not meant to resume!!
        CLOSE_GOING_AWAY = 1001, //Unresumable! Considered a graceful shutdown not meant to resume!!
        CLOSE_PROTOCOL_ERROR = 1002,
        CLOSE_UNSUPPORTED = 1003,
        CLOSE_NO_STATUS = 1005,
        UNSUPPORTED_PAYLOAD = 1006,
        POLICY_VIOLATION = 1008,
        CLOSE_TOO_LARGE = 1009,
        MANDATORY_EXTENTION = 1010,
        SERVER_ERROR = 1011,
        SERVER_RESTART = 1012,
        TRY_AGAIN_LATER = 1013,
        BAD_GATEWAY = 1014,
        TLS_HANDSHAKE_FAIL = 1015,
        UNKNOWN_ERROR = 4000,
        UNKNOWN_OPCODE = 4001,
        DECODE_ERROR = 4002,
        NOT_AUTHENTICATED = 4003,
        AUTHENTICATION_FAILED = 4004,
        ALREADY_AUTHENTICATED = 4005,
        INVALID_SEQ = 4007,
        RATE_LIMITED = 4008,
        SESSION_TIMED_OUT = 4009,
        INVALID_SHARD = 4010,
        SHARDING_REQUIRED = 4011,
        INVALID_API_VERSION = 4012,
        INVALID_INTENTS = 4013,
        DISALLOWED_INTENTS = 4014
    };
    Q_ENUM(CloseCodes)

    enum Intents {
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
        DIRECT_MESSAGE_TYPING = 14,
        ALL_INTENTS = 15
    };
    Q_ENUM(Intents)

    void init();

public slots:
    void sendTextMessage(QSharedPointer<GatewayPayload> payload);
    void sendBinaryMessage(QSharedPointer<GatewayPayload> payload);

Q_SIGNALS:
    void dispatchEvent(QSharedPointer<GatewayPayload> payload);
    void guildOnline(QSharedPointer<GatewayPayload> payload);
    void defaultGuildOnline(QSharedPointer<GuildEntity> payload);
};

#endif // GATEWAYCONNECTION_H
