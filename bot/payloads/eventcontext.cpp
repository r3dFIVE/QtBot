#include "eventcontext.h"


const QString EventContext::CHANNEL_ID = "channel_id";
const QString EventContext::GUILD_ID = "guild_id";
const QString EventContext::CONTENT = "content";
const QString EventContext::AUTHOR = "author";
const QString EventContext::COMMAND = "command";
const QString EventContext::SOURCE_PAYLOAD = "source_payload";
const QString EventContext::TARGET_PAYLOAD = "target_payload";

QJsonValue
EventContext::getChannelId() const {
    return _jsonObject[CHANNEL_ID];
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
EventContext::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonValue
EventContext::getContent() const {
    return _jsonObject[CONTENT];
}

void
EventContext::setContent(const QJsonValue &content) {
    _jsonObject[CONTENT] = content;
}

QJsonValue
EventContext::getCommand() const {
    return _jsonObject[COMMAND];
}

void
EventContext::setCommand(const QJsonValue &value) {
    _jsonObject[COMMAND] = value;
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
