#include "gateway.h"

#include <QSettings>
#include <QThread>

#include "logging/logfactory.h"
#include "payloads/guild.h"
#include "payloads/hello.h"
#include "payloads/identify.h"
#include "payloads/identifyproperties.h"
#include "payloads/ready.h"
#include "payloads/resume.h"
#include "util/globals.h"
#include "util/enumutils.h"



Gateway::Gateway(QSharedPointer<Settings> settings)
{    
    _botToken = settings->value(SettingsParam::Connection::BOT_TOKEN).toString();

    _maxRetries = settings->value(SettingsParam::Connection::MAX_RETRIES).toInt();

    _lastSequenceNumber = -1;

    _retryCount = 0;

    _heartbeatAck = true;

    _attemptResume = false;

    _logger = LogFactory::getLogger();

    _gateway = buildConnectionUrl(settings);
}

Gateway::~Gateway() {
    closeConnection(QWebSocketProtocol::CloseCodeNormal);
}

void
Gateway::init() {
    _socket = QSharedPointer<QWebSocket>(new QWebSocket);

    connect(_socket.data(), &QWebSocket::connected, this, [&](){
        _logger->info("Gateway connection established.");
    });

    connect(_socket.data(), QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &Gateway::onSocketError);

    connect(_socket.data(), &QWebSocket::textMessageReceived, this, &Gateway::onTextMessageReceived);

    connect(_socket.data(), &QWebSocket::binaryMessageReceived, this, &Gateway::onBinaryMessageReceived);

    connect(_socket.data(), &QWebSocket::disconnected, this, &Gateway::onDisconnected);

    _heartbeatTimer = QSharedPointer<QTimer>( new QTimer(this));

    connect(_heartbeatTimer.data(), &QTimer::timeout, this, &Gateway::sendHeartbeat);

    _socket->open(_gateway);
}

void
Gateway::onSocketError(QAbstractSocket::SocketError errorCode) {

    _logger->debug(QString("QSocketError: %1, %2. Shutting down...")
                   .arg(errorCode)
                   .arg(EnumUtils::valueToKey(errorCode)));

    if (_retryCount++ <= _maxRetries) {
        reconnect(MS_FIVE_SECONDS);
    } else {
        tooManyReconnects();
    }
}

void
Gateway::onDisconnected() {
    int closeCode = _socket->closeCode();

    QString closeReason = EnumUtils::valueToKey(CloseCodes(closeCode));

    _logger->debug(QString("Socket closed with code: %1 %2").arg(closeCode).arg(closeReason));

    if (++_retryCount <= _maxRetries) {
        switch (closeCode) {
        case QWebSocketProtocol::CloseCodeNormal:
        case QWebSocketProtocol::CloseCodeGoingAway:
        case QWebSocketProtocol::CloseCodeAbnormalDisconnection:
        case QWebSocketProtocol::CloseCodeTooMuchData:
            reconnect(MS_FIVE_SECONDS);

            break;
        case QWebSocketProtocol::CloseCode(CloseCodes::SERVER_RESTART):
            reconnect(IMMEDIATE);

            break;
        default:
            _logger->fatal(QString("Bot has received an unrecoverable close code %1 (%2), shutting down...")
                    .arg(closeCode).arg(closeReason));

            exit(EXIT_FAILURE);
        }
    } else {
        tooManyReconnects();
    }
}

void
Gateway::tooManyReconnects() {
    _logger->fatal(QString("Bot has reached maxium number of recconect attempts (%1), shutting down...")
            .arg(_maxRetries));

    exit(EXIT_FAILURE);
}

void
Gateway::reconnect(int mSleep) {
    QThread::msleep(mSleep);

    _logger->debug(QString("Reconnect attempt %1/%2.").arg(_retryCount).arg(_maxRetries));

    _socket->open(_gateway);
}

void
Gateway::onTextMessageReceived(const QString &message) {
    _logger->trace("Message recieved: " + message);

    QSharedPointer<GatewayPayload> event(new GatewayPayload);

    event->fromQString(message);

    processPayload(event);
}

void
Gateway::onBinaryMessageReceived(QByteArray messageArray) {
    _logger->trace("Message recieved: " + messageArray);

    QSharedPointer<GatewayPayload> event(new GatewayPayload);

    event->fromByteArray(messageArray);

    processPayload(event);
}

void
Gateway::processPayload(QSharedPointer<GatewayPayload> payload) {
    switch(payload->getOp().toInt()) {
    case GatewayEvent::HELLO:
        processHello(payload);

        break;
    case GatewayEvent::HEARTBEAT:
        sendHeartbeat();

        break;
    case GatewayEvent::HEARTBEAT_ACK:
        processAck();

        break;
    case GatewayEvent::DISPATCH:
        processDispatch(payload);

        break;
    case GatewayEvent::INVALID_SESSION:
        processInvalidSession(payload);

        break;
    case GatewayEvent::RECONNECT:
        processReconnect();

        break;
    }
}

void
Gateway::closeConnection(QWebSocketProtocol::CloseCode closeCode) {
    _heartbeatTimer->stop();

    _socket->close(closeCode);
}

void
Gateway::processReconnect() {
    _logger->debug("RECONNECT event dispatched, attemping to reconnect...");

    closeConnection(QWebSocketProtocol::CloseCode(CloseCodes::SERVER_RESTART));
}


void
Gateway::processDispatch(QSharedPointer<GatewayPayload> payload) {
    _lastSequenceNumber = payload->getS().toInt();

    GatewayEvent::Event gatewayEvent = EnumUtils::keyToValue<GatewayEvent::Event>(payload->getT());

    switch (gatewayEvent) {
    case GatewayEvent::READY:
        processReady(payload);
        return;
    case GatewayEvent::RESUMED:
        processResumed(payload);
        return;
    case GatewayEvent::GUILD_CREATE:
        processGuildCreate(payload);
        return;
    }

    emit dispatchEvent(payload);
}

void
Gateway::processInvalidSession(QSharedPointer<GatewayPayload> payload) {
    bool isResumable = payload->getV().toBool();

    if (isResumable) {
        sendResume();
    } else {
        _attemptResume = false;

        closeConnection(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
    }
}

void
Gateway::processReady(QSharedPointer<GatewayPayload> payload) {
    _logger->info("Gateway connection established. Bot will join guilds shortly!");

    Ready ready(payload->getD());

    _sessionId = ready.getSessionId().toString();

    _retryCount = 0;
}

void
Gateway::processResumed(QSharedPointer<GatewayPayload> payload) {
    _logger->info("Gateway connection sucessfully resumed.");

    _retryCount = 0;
}

void
Gateway::processAck() {
    _logger->trace(QString("ACK receieved."));

    _heartbeatAck = true;
}

void
Gateway::sendTextMessage(QSharedPointer<GatewayPayload> payload) {
    QString messageStr = payload->toQString();

    _socket->sendTextMessage(messageStr);

    _logger->trace("Sent gateway payload: " + messageStr);
}

void
Gateway::sendBinaryMessage(QSharedPointer<GatewayPayload> payload) {
    _socket->sendBinaryMessage(payload->toByteArray());
}

void
Gateway::processHello(QSharedPointer<GatewayPayload> payload) {
    Hello helloEvent(payload->getD());

    _heartbeatAck = true;

    _heartbeatTimer->stop();

    _heartbeatTimer->setInterval(helloEvent.getHeartbeatInterval());

    _heartbeatTimer->start();

    if (_attemptResume) {
        sendResume();
    } else {
        sendIdentify();

        _attemptResume = true;
    }
}

void
Gateway::sendIdentify() {
    //TODO add and pull intents from settings file
    int intents = 0;

    intents |= (1 << GUILDS) | (1 << GUILD_MEMBERS) | (1 << GUILD_MESSAGES) | (1 << DIRECT_MESSAGES) | (1 << GUILD_MESSAGE_TYPING);

    Identify identify;

    identify.setToken(_botToken);

    identify.setIntents(intents);

    IdentifyProperties properties;

    identify.setProperties(properties.toQJsonObject());

    GatewayPayload payload;

    payload.setOp(GatewayEvent::IDENTIFY);

    payload.setD(identify.toQJsonObject());

    sendTextPayload(payload.toQString());
}

void
Gateway::sendResume() {    
    Resume resume;

    resume.setToken(_botToken);

    resume.setSessionId(_sessionId);

    resume.setSeq(_lastSequenceNumber);

    GatewayPayload payload;

    payload.setOp(GatewayEvent::RESUME);

    payload.setD(resume.toQJsonObject());

    sendTextPayload(payload.toQString());
}

void
Gateway::sendHeartbeat() {
    if (_heartbeatAck) {
        _heartbeat.setD(_lastSequenceNumber);

        sendTextPayload(_heartbeat.toQString());

        _heartbeatAck = false;
    } else {
        _logger->warning("No Heartbeat ack received from previous heartbeat, attemping to reconnect...");

        closeConnection(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
    }
}

void
Gateway::sendTextPayload(const QString &payload) {
    _socket->sendTextMessage(payload);

    _logger->trace(QString("Payload sent: %1").arg(payload));
}

QUrl
Gateway::buildConnectionUrl(QSharedPointer<Settings> settings) {
    QString baseUrl = settings->value(SettingsParam::Connection::CONNECTION_URL).toString();

    bool zlibEnabled = settings->value(SettingsParam::Connection::ZLIB_ENABLED).toBool();

    QString zlibParameter = "";

    if (zlibEnabled) {
        zlibParameter = "&compress=zlib-stream";
    }

    return QUrl(QString("%1/?v=6&encoding=json%2")
                .arg(baseUrl)
                .arg(zlibParameter));
}

void
Gateway::processGuildCreate(QSharedPointer<GatewayPayload> payload) {
    emit guildOnline(payload->getD()[Guild::ID].toString());
}
