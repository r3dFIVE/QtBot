/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "gateway.h"

#include <QSettings>
#include <QThread>

#include "botjob/botscript.h"
#include "logging/logfactory.h"
#include "payloads/guild.h"
#include "payloads/hello.h"
#include "payloads/identify.h"
#include "payloads/identifyproperties.h"
#include "payloads/ready.h"
#include "payloads/resume.h"
#include "payloads/user.h"
#include "routes/discordapi.h"
#include "util/enumutils.h"
#include "util/httputils.h"

const int Gateway::MS_TEN_SECONDS = 10000;
const int Gateway::IMMEDIATE = 0;

Gateway::Gateway()
{    
    _botToken = Settings::botToken();

    _maxRetries = Settings::maxRetries();

    _logger = LogFactory::getLogger(this);

    _gatewayUrl = buildConnectionUrl(Settings::connectionUrl());

    calculateGatewayIntents();
}

Gateway::~Gateway() {
    _shutdown = true;

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

    _socket->open(_gatewayUrl);



    emit defaultGuildOnline(QSharedPointer<GuildEntity>(new GuildEntity));
}

void
Gateway::onSocketError(QAbstractSocket::SocketError errorCode) {

    _logger->debug(QString("QSocketError: %1, %2. Shutting down...")
                   .arg(errorCode)
                   .arg(EnumUtils::valueToKey(errorCode)));

    if (_retryCount++ <= _maxRetries) {
        reconnect(MS_TEN_SECONDS);
    } else {
        tooManyReconnects();
    }
}

void
Gateway::onDisconnected() {
    if (_shutdown) {
        return;
    }

    int closeCode = _socket->closeCode();

    QString closeReason = EnumUtils::valueToKey(CloseCodes(closeCode));

    _logger->debug(QString("Socket closed with code: %1 %2").arg(closeCode).arg(closeReason));

    if (++_retryCount <= _maxRetries) {
        switch (closeCode) {
        case QWebSocketProtocol::CloseCodeNormal:
        case QWebSocketProtocol::CloseCodeGoingAway:
        case QWebSocketProtocol::CloseCodeAbnormalDisconnection:
        case QWebSocketProtocol::CloseCodeTooMuchData:
            reconnect(MS_TEN_SECONDS);

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

    _heartbeatTimer->stop();

    _logger->debug(QString("Reconnect attempt %1/%2.").arg(_retryCount).arg(_maxRetries));

    _socket->open(_resumeGatewayUrl);
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
Gateway::calculateGatewayIntents() {

    QStringList intentTokens = Settings::gatewayIntents().split(",");

    if (intentTokens.contains(EnumUtils::valueToKey(ALL_INTENTS))) {
        _gatewayIntents = (0 | (1 << ALL_INTENTS)) - 1;

    } else {
        for (QString intent : intentTokens) {
            int value = EnumUtils::keyToValue<Gateway::Intents>(intent);

            _gatewayIntents |= (1 << value);
        }
    }
}

void
Gateway::closeConnection(QWebSocketProtocol::CloseCode closeCode) {
    _heartbeatTimer->stop();

    _socket->close(closeCode);
}

void
Gateway::processReconnect() {
    _logger->info("RECONNECT event dispatched, attemping to reconnect...");

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
        processResumed();
        return;
    case GatewayEvent::GUILD_CREATE:
        processGuildCreate(payload);
        return;
    default:
        break;
    }

    emit dispatchEvent(gatewayEvent, payload);
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

    User botUser(ready.getUser());

    BotScript::setBotId(botUser.getId().toString());

    BotScript::setBotName(botUser.getUsername().toString());

    BotScript::setBotOwnerId(Settings::ownerId());

    _resumeGatewayUrl = buildConnectionUrl(ready.getResumeGatewayUrl().toString());
}

void
Gateway::processResumed() {
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
    Identify identify;

    identify.setToken(_botToken);

    identify.setIntents(_gatewayIntents);

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
Gateway::buildConnectionUrl(const QString &baseUrl) const {
    return QUrl(QString("%1/?v=%2&encoding=json")
                .arg(baseUrl)
                .arg(Settings::apiVersion()));
}

void
Gateway::processGuildCreate(QSharedPointer<GatewayPayload> payload) {
    emit guildOnline(payload);
}
