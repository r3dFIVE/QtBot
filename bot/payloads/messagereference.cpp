#include "messagereference.h"


const QString MessageReference::CHANNEL_ID = "channel_id";
const QString MessageReference::GUILD_ID = "guild_id";
const QString MessageReference::MESSAGE_ID = "message_id";

QJsonValue
MessageReference::getMessageId() const {
    return _jsonObject[MESSAGE_ID];
}
void
MessageReference::setMessageId(const QJsonValue &messageId) {
    _jsonObject[MESSAGE_ID] = messageId;
}

QJsonValue
MessageReference::getChannelId() const {
    return _jsonObject[CHANNEL_ID];
}

void
MessageReference::setChannelId(const QJsonValue &channelId) {
    _jsonObject[CHANNEL_ID] = channelId;
}

QJsonValue
MessageReference::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
MessageReference::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}
