#include "messagereference.h"

#include "util/jsonutils.h"


QJsonValue
MessageReference::getMessageId() const {
    return message_id;
}
void
MessageReference::setMessageId(const QJsonValue &value) {
    message_id = value;
}

QJsonValue
MessageReference::getChannelId() const {
    return channel_id;
}

void
MessageReference::setChannelId(const QJsonValue &value) {
    channel_id = value;
}

QJsonValue
MessageReference::getGuildId() const {
    return guild_id;
}

void
MessageReference::setGuildId(const QJsonValue &value) {
    guild_id = value;
}

void
MessageReference::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
MessageReference::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
