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

#include "eventcontext.h"

#include "entity/guildentity.h"
#include "util/enumutils.h"


const QString EventContext::ID = "id";
const QString EventContext::EVENT_NAME = "event_name";
const QString EventContext::EMOJI = "emoji";
const QString EventContext::CHANNEL_ID = "channel_id";
const QString EventContext::GUILD_ID = "guild_id";
const QString EventContext::INTEGRATION_ID = "integration_id";
const QString EventContext::INVITE_CODE = "invite_code";
const QString EventContext::ROLES = "roles";
const QString EventContext::ROLE_ID = "role_id";
const QString EventContext::ROLE_IDS = "role_ids";
const QString EventContext::MESSAGE_ID = "message_id";
const QString EventContext::OVERWRITE_ID = "overwrite_id";
const QString EventContext::WEBHOOK_ID = "webhook_id";
const QString EventContext::WEBHOOK_TOKEN = "webhook_token";
const QString EventContext::USER_ID = "user_id";
const QString EventContext::JOB_ID = "job_id";
const QString EventContext::CONTENT = "content";
const QString EventContext::MEMBER = "member";
const QString EventContext::ARGS = "args";
const QString EventContext::AUTHOR = "author";
const QString EventContext::USERNAME = "username";
const QString EventContext::QUERY_PARAMS = "query_params";
const QString EventContext::SOURCE_PAYLOAD = "source_payload";
const QString EventContext::TARGET_PAYLOAD = "target_payload";
const QString EventContext::RECIPIENT_ID = "recipient_id";

EventContext::EventContext(const QByteArray &json, QObject *parent) : JsonSerializable(parent) {
    buildContext(QJsonDocument::fromJson(json).object());
}

EventContext::EventContext(const QJsonObject &json, QObject *parent) : JsonSerializable(parent) {
    buildContext(json);
}

EventContext::EventContext(const EventContext &other, QObject *parent) : JsonSerializable(parent) {
    buildContext(other._jsonObject);
}

void
EventContext::processEventParams(const GatewayEvent::Event event, const QString &mainParamKey) {
    _jsonObject[EVENT_NAME] = EnumUtils::valueToKey<GatewayEvent::Event>(event);

    if (!mainParamKey.isEmpty()) {
        _jsonObject[mainParamKey] = _jsonObject[SOURCE_PAYLOAD].toObject()[ID];
    }
}

void
EventContext::buildContext(const QJsonObject &json) {
    _jsonObject = json;

    if (json[TARGET_PAYLOAD].isUndefined()) {
        _jsonObject[TARGET_PAYLOAD] = QJsonObject();
    }

    if (json.contains(SOURCE_PAYLOAD)) {
        _jsonObject[SOURCE_PAYLOAD] = json[SOURCE_PAYLOAD];
    } else {
        _jsonObject[SOURCE_PAYLOAD] = json;

        if (json.contains(MEMBER)) {
            _jsonObject[ROLE_IDS] = json[MEMBER][ROLES];
        }

        if (json.contains(QUERY_PARAMS)) {
            _jsonObject[QUERY_PARAMS] = json[QUERY_PARAMS];
        } else {
            _jsonObject[QUERY_PARAMS] = QJsonObject();
        }

        if (json.contains(AUTHOR) && !json[AUTHOR][ID].isUndefined()) {
            _jsonObject[USER_ID] = json[AUTHOR][ID];
        }

        if (json.contains(CONTENT)) {
            _jsonObject[CONTENT] = _jsonObject[CONTENT];

            splitArgs();
        }

        if (!json.contains(GUILD_ID)){
            _jsonObject[GUILD_ID] = GuildEntity::DEFAULT_GUILD_ID;
        }
    }
}

QJsonArray
EventContext::getArgs() const {
    return _jsonObject[ARGS].toArray();
}

void
EventContext::setArgs(const QJsonArray &args) const {
    _jsonObject[ARGS] = args;
}

QJsonValue
EventContext::getEventName() const {
    return _jsonObject[EVENT_NAME];
}

void
EventContext::setEventName(const QJsonValue &eventName) {
    _jsonObject[EVENT_NAME] = eventName;
}

QJsonValue
EventContext::getChannelId() const {
    return _jsonObject[CHANNEL_ID];
}

void
EventContext::setOverwriteId(const QJsonValue &channelId) {
    _jsonObject[OVERWRITE_ID] = channelId;
}

QJsonValue
EventContext::getOverwriteId() const {
    return _jsonObject[OVERWRITE_ID];
}

void
EventContext::setChannelId(const QJsonValue &channelId) {
    _jsonObject[CHANNEL_ID] = channelId;
}

QJsonValue
EventContext::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
EventContext::setUserId(const QJsonValue &userId) {
    _jsonObject[USER_ID] = userId;
}

QJsonValue
EventContext::getUserId() const {
    return _jsonObject[USER_ID];
}

void
EventContext::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonValue
EventContext::getRoleId() const {
    return _jsonObject[ROLE_ID];
}

void
EventContext::setRoleId(const QJsonValue &roleId) {
    _jsonObject[ROLE_ID] = roleId;
}

const QJsonArray
EventContext::getRoleIds() const {
    return _jsonObject[ROLE_IDS].toArray();
}

void
EventContext::setRoleIds(const QJsonValue &roleId) {
    _jsonObject[ROLE_ID] = roleId;
}

QJsonValue
EventContext::getMessageId() const {
    return _jsonObject[MESSAGE_ID];
}

void
EventContext::setMessageId(const QJsonValue &messageId) {
    _jsonObject[MESSAGE_ID] = messageId;
}

QJsonValue
EventContext::getWebhookId() const {
    return _jsonObject[WEBHOOK_ID];
}

void
EventContext::setWebhookId(const QJsonValue &webhookId) {
    _jsonObject[WEBHOOK_ID] = webhookId;
}

QJsonValue
EventContext::getWebhookToken() const {
    return _jsonObject[WEBHOOK_TOKEN];
}

void
EventContext::setWebhookToken(const QJsonValue &webhookToken) {
    _jsonObject[WEBHOOK_TOKEN] = webhookToken;
}


void
EventContext::splitArgs() {
    QString content = _jsonObject[CONTENT].toString();

    if (content.isEmpty()) {
        _jsonObject[ARGS] = QJsonArray();
    } else {
        _jsonObject[ARGS] = QJsonArray::fromStringList(content.split(" "));
    }
}

QJsonValue
EventContext::getIntegrationId() const {
    return _jsonObject[INTEGRATION_ID];
}

void
EventContext::setIntegrationId(const QJsonValue &integrationId) {
    _jsonObject[INTEGRATION_ID] = integrationId;
}

QJsonValue
EventContext::getInviteCode() const {
    return _jsonObject[INVITE_CODE];
}

void
EventContext::setInviteCode(const QJsonValue &inviteCode) {
    _jsonObject[INVITE_CODE] = inviteCode;
}

QJsonValue
EventContext::getContent() const {
    return _jsonObject[CONTENT];
}

void
EventContext::setEmoji(const QJsonValue &emoji) {
    _jsonObject[EMOJI] = emoji;
}

QJsonValue
EventContext::getEmoji() const {
    return _jsonObject[EMOJI];
}

void
EventContext::setJobId(const QJsonValue &jobId) {
    _jsonObject[JOB_ID] = jobId;
}

QJsonValue
EventContext::getJobId() const {
    return _jsonObject[JOB_ID];
}


void
EventContext::setContent(const QJsonValue &content) {
    _jsonObject[CONTENT] = content;

    splitArgs();
}

QJsonValue
EventContext::getUsername() const {
    return _jsonObject[USERNAME];
}

void
EventContext::setUsername(const QJsonValue &value) {
    _jsonObject[USERNAME] = value;
}

QJsonObject
EventContext::getAuthor() const {
    return _jsonObject[AUTHOR].toObject();
}

void
EventContext::setAuthor(const QJsonObject &value) {
    _jsonObject[AUTHOR] = value;
}

QJsonObject
EventContext::getQueryParams() const {
    return _jsonObject[QUERY_PARAMS].toObject();
}

void
EventContext::setQueryParams(const QJsonObject &queryParams) {
    _jsonObject[QUERY_PARAMS] = queryParams;
}

QJsonObject
EventContext::getSourcePayload() const {
    return _jsonObject[SOURCE_PAYLOAD].toObject();
}

void
EventContext::setSourcePayload(const QJsonObject &sourcePayload) {
    _jsonObject[SOURCE_PAYLOAD] = sourcePayload;
}

QJsonObject
EventContext::getTargetPayload() const {
    return _jsonObject[TARGET_PAYLOAD].toObject();
}

void
EventContext::setTargetPayload(const QJsonObject &targetPayload) {
    _jsonObject[TARGET_PAYLOAD] = targetPayload;
}
