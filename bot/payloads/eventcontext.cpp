#include "eventcontext.h"


const QString EventContext::EVENT_NAME = "event_name";
const QString EventContext::CHANNEL_ID = "channel_id";
const QString EventContext::GUILD_ID = "guild_id";
const QString EventContext::CONTENT = "content";
const QString EventContext::AUTHOR = "author";
const QString EventContext::SOURCE_PAYLOAD = "source_payload";
const QString EventContext::TARGET_PAYLOAD = "target_payload";

EventContext::EventContext(const QByteArray &json) {
    buildContext(QJsonDocument::fromJson(json).object());
}

EventContext::EventContext(const QJsonObject &json) {
    buildContext(json);
}

void
EventContext::buildContext(const QJsonObject &json) {
    _jsonObject[EVENT_NAME] = json[EVENT_NAME];
    _jsonObject[CHANNEL_ID] = json[CHANNEL_ID];
    _jsonObject[GUILD_ID] = json[GUILD_ID];
    _jsonObject[CONTENT] = json[CONTENT];
    _jsonObject[AUTHOR] = json[AUTHOR];
    _jsonObject[SOURCE_PAYLOAD] = json;
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
