#include "eventcontext.h"

#include "util/globals.h"


const QString EventContext::ID = "id";
const QString EventContext::EVENT_NAME = "event_name";
const QString EventContext::EMOJI = "emoji";
const QString EventContext::CHANNEL_ID = "channel_id";
const QString EventContext::GUILD_ID = "guild_id";
const QString EventContext::INTEGRATION_ID = "integration_id";
const QString EventContext::ROLES = "roles";
const QString EventContext::ROLE_ID = "role_id";
const QString EventContext::ROLE_IDS = "role_ids";
const QString EventContext::MESSAGE_ID = "message_id";
const QString EventContext::OVERWRITE_ID = "overwrite_id";
const QString EventContext::WEBHOOK_ID = "webhook_id";
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
    if (json.contains(EVENT_NAME)) {
        _jsonObject[EVENT_NAME] = json[EVENT_NAME];
    }

    if (json.contains(ROLE_ID)) {
        _jsonObject[ROLE_ID] = json[ROLE_ID];
    }

    if (json.contains(OVERWRITE_ID)) {
        _jsonObject[OVERWRITE_ID] = json[OVERWRITE_ID];
    }

    if (json.contains(CHANNEL_ID)) {
        _jsonObject[CHANNEL_ID] = json[CHANNEL_ID];
    }

    if (json.contains(GUILD_ID)) {
        _jsonObject[GUILD_ID] = json[GUILD_ID];
    } else {
        _jsonObject[GUILD_ID] = DEFAULT_GUILD_ID;
    }

    if (json.contains(INTEGRATION_ID)) {
        _jsonObject[INTEGRATION_ID] = json[INTEGRATION_ID];
    }

    if (json.contains(USER_ID)) {
        _jsonObject[USER_ID] = json[USER_ID];
    }

    if (json.contains(WEBHOOK_ID)) {
        _jsonObject[WEBHOOK_ID] = json[WEBHOOK_ID];
    }

    if (json.contains(CONTENT)) {
        _jsonObject[CONTENT] = json[CONTENT];
    }

    if (json.contains(AUTHOR)) {
        _jsonObject[AUTHOR] = json[AUTHOR];

        _jsonObject[USER_ID] = json[AUTHOR][ID];
    }

    if (json.contains(MEMBER)) {
        _jsonObject[ROLE_IDS] = json[MEMBER][ROLES];
    } else if (json.contains(ROLE_IDS)) {
        _jsonObject[ROLE_IDS] = json[ROLE_IDS];
    }

    if (json.contains(EMOJI)) {
        _jsonObject[EMOJI] = json[EMOJI];
    }

    if (json.contains(MESSAGE_ID)) {
        _jsonObject[MESSAGE_ID] = json[MESSAGE_ID];
    }

    if (json.contains(JOB_ID)) {
        _jsonObject[JOB_ID] = json[JOB_ID];
    }

    if (json.contains(QUERY_PARAMS)) {
        _jsonObject[QUERY_PARAMS] = json[QUERY_PARAMS];
    } else {
        _jsonObject[QUERY_PARAMS] = QJsonObject();
    }

    if (json.contains(TARGET_PAYLOAD)) {
        _jsonObject[TARGET_PAYLOAD] = json[TARGET_PAYLOAD];
    } else {
        _jsonObject[TARGET_PAYLOAD] = QJsonObject();
    }

    if (json.contains(SOURCE_PAYLOAD)) {
        _jsonObject[SOURCE_PAYLOAD] = json[SOURCE_PAYLOAD];
    } else {
        _jsonObject[SOURCE_PAYLOAD] = json;
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

QJsonArray
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
