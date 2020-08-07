#include "channelmention.h"

const QString ChannelMention::ID = "id";
const QString ChannelMention::GUILD_ID = "guild_id";
const QString ChannelMention::TYPE = "type";
const QString ChannelMention::NAME = "name";

QJsonValue
ChannelMention::getId() const {
    return _jsonObject[ID];
}

void
ChannelMention::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
ChannelMention::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
ChannelMention::setGuildId(const QJsonValue &guild_id) {
    _jsonObject[ID] = guild_id;
}

QJsonValue
ChannelMention::getType() const {
    return _jsonObject[TYPE];
}

void
ChannelMention::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
ChannelMention::getName() const {
    return _jsonObject[NAME];
}

void
ChannelMention::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

