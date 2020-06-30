#include "gateway.h"
#include "util/globals.h"
#include "payloads/hello.h"
#include "logging/logfactory.h"
#include "payloads/resume.h"
#include "payloads/identify.h"
#include "payloads/ready.h"

#include <QSettings>
#include <QThread>


Gateway::Gateway(QSharedPointer<Settings> settings, QObject *parent) :
    QObject(parent),
    _maxRetries(settings->value(SettingsParam::Connection::MAX_RETRIES).toInt())
{    
    _botToken = settings->value(SettingsParam::Connection::BOT_TOKEN).toString();
    _lastSequenceNumber = -1;
    _retryCount = 0;
    _heartbeatAck = true;
    _resume = false;
    _logger = LogFactory::init(settings);
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

    connect(_socket.data(), QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
        [=](QAbstractSocket::SocketError errorCode) {
            QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
            QString errorReason = metaEnum.valueToKey(errorCode);
            _logger->critical(QString("QSocketError: %1, %2. Shutting down...").arg(errorCode).arg(errorReason));
            exit(1);
        }
    );

    connect(_socket.data(), &QWebSocket::textMessageReceived, this, &Gateway::onTextMessageReceived);
    connect(_socket.data(), &QWebSocket::binaryMessageReceived, this, &Gateway::onBinaryMessageReceived);
    connect(_socket.data(), &QWebSocket::disconnected, this, &Gateway::onDisconnected);
    _heartbeatTimer = QSharedPointer<QTimer>( new QTimer(this));
    connect(_heartbeatTimer.data(), &QTimer::timeout, this, &Gateway::sendHeartbeat);

    _socket->open(_gateway);
}

void
Gateway::onDisconnected() {
    int closeCode = _socket->closeCode();

    QMetaEnum metaEnum = QMetaEnum::fromType<GatewayCloseCodes>();
    QString closeReason = metaEnum.valueToKey(closeCode);

    _logger->debug(QString("Socket closed with code: %1 %2").arg(closeCode).arg(closeReason));

    if (_retryCount++ <= _maxRetries) {
        switch (closeCode) {
        case QWebSocketProtocol::CloseCodeAbnormalDisconnection:
        case QWebSocketProtocol::CloseCodeGoingAway:
            QThread::msleep(5000);
            reconnect();
            break;
        case QWebSocketProtocol::CloseCode(GatewayCloseCodes::SERVER_RESTART):
            reconnect();
            break;
        default:
            _logger->warning(QString("Bot has received an unrecoverable close code %1 (%2), shutting down...")
                    .arg(closeCode).arg(closeReason));
            break;
        }
    } else {
        _logger->warning(QString("Bot has reached maxium number of recconect attempts (%1), shutting down...")
                .arg(_maxRetries));
        exit(1);
    }
}

void
Gateway::reconnect() {
    _logger->debug(QString("Reconnect attempt %1/%2.").arg(_retryCount).arg(_maxRetries));
    _socket->open(_gateway);
}

void
Gateway::onTextMessageReceived(QString message) {
    _logger->trace("Message recieved: " + message);
    QSharedPointer<GatewayPayload::GatewayPayload> event(new GatewayPayload::GatewayPayload);
    event->fromQString(message);
    processPayload(event);
}

void
Gateway::onBinaryMessageReceived(QByteArray messageArray) {
    _logger->trace("Message recieved: " + messageArray);
    QSharedPointer<GatewayPayload::GatewayPayload> event(new GatewayPayload::GatewayPayload);
    event->fromByteArray(messageArray);
    processPayload(event);
}

void
Gateway::processPayload(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    switch(payload->op) {
        case GatewayEvents::HELLO:
            processHello(payload);
            break;
        case GatewayEvents::HEARTBEAT:
            sendHeartbeat();
            break;
        case GatewayEvents::HEARTBEAT_ACK:
            processAck();
            break;
        case GatewayEvents::DISPATCH:
            processDispatch(payload);
            break;
        case GatewayEvents::INVALID_SESSION:
            processInvalidSession(payload);
            break;
        case GatewayEvents::RECONNECT:
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
    closeConnection(QWebSocketProtocol::CloseCode(GatewayCloseCodes::SERVER_RESTART));
}


void
Gateway::processDispatch(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    _lastSequenceNumber = payload->s;

    //TODO MetaUtils::keyToValue( T t, QString key); or something
    QMetaEnum metaEnum = QMetaEnum::fromType<GatewayEvents::Events>();
    int eventCode = metaEnum.keyToValue(payload->t.toUtf8());

    switch (eventCode) {
    case GatewayEvents::READY:
        processReady(payload);
        break;
    case GatewayEvents::RESUMED:
        processResumed(payload);
        break;
    }

    emit dispatchEvent(payload);
}

void
Gateway::processInvalidSession(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    bool isResumable = payload->d[GatewayPayload::VALUE].toBool();
    if (isResumable) {
        sendResume();
    } else {
        _resume = false;
        closeConnection(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
    }
}

void
Gateway::processReady(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    _logger->info("Gateway connection established. Bot will join guilds shortly!");

    Ready ready;
    ready.fromQJsonObject(payload->d);

    _sessionId = ready.getSessionId();
    _retryCount = 0;
}

void
Gateway::processResumed(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    _logger->info("Gateway connection sucessfully resumed.");
    _retryCount = 0;
}

void
Gateway::processAck() {
    _logger->trace(QString("ACK receieved."));
    _heartbeatAck = true;
}

void
Gateway::sendTextMessage(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    QString messageStr = payload->toQString();
    _socket->sendTextMessage(messageStr);
    _logger->trace("Sent gateway payload: " + messageStr);
}

void
Gateway::sendBinaryMessage(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    _socket->sendBinaryMessage(payload->toByteArray());
}

void
Gateway::processHello(QSharedPointer<GatewayPayload::GatewayPayload> payload) {
    Hello helloEvent;
    helloEvent.read(payload->d);

    _heartbeatTimer->stop();
    _heartbeatTimer->setInterval(*helloEvent.heartbeat_interval);
    _heartbeatTimer->start();

    if (_resume) {
        sendResume();
    } else {
        sendIdentify();
        _resume = true;
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

    GatewayPayload::GatewayPayload payload;
    payload.op = GatewayEvents::IDENTIFY;
    identify.write(payload.d);

    sendTextPayload(payload.toQString());
}

void
Gateway::sendResume() {    
    Resume resume;
    resume.token = _botToken;
    resume.session_id = _sessionId;
    resume.seq = _lastSequenceNumber;

    GatewayPayload::GatewayPayload payload;
    payload.op = GatewayEvents::RESUME;
    resume.write(payload.d);

    sendTextPayload(payload.toQString());
}

void
Gateway::sendHeartbeat() {
    if (_heartbeatAck) {
        _heartbeat.d = _lastSequenceNumber;
        sendTextPayload(_heartbeat.toQString());
        _heartbeatAck = false;
    } else {
        _logger->warning("No Heartbeat ack received from previous heartbeat, attemping to reconnect...");
        closeConnection(QWebSocketProtocol::CloseCodeAbnormalDisconnection);
    }
}

void
Gateway::sendTextPayload(QString payload) {
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

    return QUrl(QString("%1/?v=6&encoding=json%2").arg(baseUrl).arg(zlibParameter));
}

