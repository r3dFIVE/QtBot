#include "eventcontext.h"
#include "util/globals.h"


const QString EventContext::ID = "id";
const QString EventContext::EVENT_NAME = "event_name";
const QString EventContext::EMOJI = "emoji";
const QString EventContext::CHANNEL_ID = "channel_id";
const QString EventContext::GUILD_ID = "guild_id";
const QString EventContext::INTEGRATION_ID = "integration_id";
const QString EventContext::ROLE_ID = "role_id";
const QString EventContext::MESSAGE_ID = "message_id";
const QString EventContext::OVERWRITE_ID = "overwrite_id";
const QString EventContext::WEBHOOK_ID = "webhook_id";
const QString EventContext::USER_ID = "user_id";
const QString EventContext::JOB_ID = "job_id";
const QString EventContext::CONTENT = "content";
const QString EventContext::ARGS = "args";
const QString EventContext::AUTHOR = "author";
const QString EventContext::USERNAME = "username";
const QString EventContext::SOURCE_PAYLOAD = "source_payload";
const QString EventContext::TARGET_PAYLOAD = "target_payload";

EventContext::EventContext(const QByteArray &json) {
    buildContext(QJsonDocument::fromJson(json).object());
}

EventContext::EventContext(const QJsonObject &json) {
    buildContext(json);
}

EventContext::EventContext(const EventContext &other) {
    buildContext(other._jsonObject);
}

void
EventContext::buildContext(const QJsonObject &json) {
    _jsonObject = json;

    if (!json[SOURCE_PAYLOAD][SOURCE_PAYLOAD].isUndefined()) {
        QJsonObject sourcePayload = _jsonObject[SOURCE_PAYLOAD].toObject();

        sourcePayload.remove(SOURCE_PAYLOAD);

        _jsonObject[SOURCE_PAYLOAD] = sourcePayload;
    }

    if (!_jsonObject.contains(GUILD_ID)) {
        _jsonObject[GUILD_ID] = DEFAULT_GUILD_ID;
    }

    if (!json[AUTHOR][ID].isUndefined()) {
        _jsonObject[USER_ID] = json[AUTHOR][ID];
    }

    if (!json[AUTHOR][USERNAME].isUndefined()) {
        _jsonObject[USERNAME] = json[AUTHOR][USERNAME];
    }

    buildArgs();
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

void
EventContext::buildArgs() {
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
EventContext::setIntegrationId(const QJsonValue &webhookId) {
    _jsonObject[INTEGRATION_ID] = webhookId;
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
EventContext::setJobId(const QJsonValue &emoji) {
    _jsonObject[JOB_ID] = emoji;
}

QJsonValue
EventContext::getJobId() const {
    return _jsonObject[JOB_ID];
}


void
EventContext::setContent(const QJsonValue &content) {
    _jsonObject[CONTENT] = content;

    buildArgs();
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
