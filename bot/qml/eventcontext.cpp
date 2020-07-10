#include "eventcontext.h"

const QString EventContext::CHANNEL_ID = "channel_id";
const QString EventContext::GUILD_ID = "guild_id";
const QString EventContext::CONTENT = "content";
const QString EventContext::AUTHOR = "author";

EventContext::EventContext(const QJsonObject &payload) {
    channel_id = payload[CHANNEL_ID];
    guild_id = payload[GUILD_ID];
    content = payload[CONTENT];
    author = payload[AUTHOR].toObject();
    source_payload = payload;
}

QJsonValue
EventContext::getChannelId() const {
    return channel_id;
}

void
EventContext::setChannelId(const QJsonValue &value) {
    channel_id = value;
}

QJsonValue
EventContext::getGuildId() const {
    return guild_id;
}

void
EventContext::setGuildId(const QJsonValue &value) {
    guild_id = value;
}

QJsonValue
EventContext::getContent() const {
    return content;
}

void
EventContext::setContent(const QJsonValue &value) {
    content = value;
}

QJsonObject
EventContext::getAuthor() const {
    return author;
}

void
EventContext::setAuthor(const QJsonObject &value) {
    author = value;
}

QJsonObject
EventContext::getSourcePayload() const {
    return source_payload;
}

void
EventContext::setSourcePayload(const QJsonObject &value) {
    source_payload = value;
}

QJsonObject
EventContext::getTargetPayload() const {
    return target_payload;
}

void
EventContext::setTargetPayload(const QJsonObject &value) {
    target_payload = value;
}
