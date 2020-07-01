#include "channelmention.h"

#include <util/jsonutils.h>

QJsonValue
ChannelMention::getId() {
    return id;
}

void
ChannelMention::setId(QJsonValue id) {
    this->id = id;
}

QJsonValue
ChannelMention::getGuildId() {
    return guild_id;
}

void
ChannelMention::setGuildId(QJsonValue guild_id) {
    this->guild_id = guild_id;
}

QJsonValue
ChannelMention::getType() {
    return type;
}

void
ChannelMention::setType(QJsonValue type) {
    this->type = type;
}

QJsonValue
ChannelMention::getName() {
    return name;
}

void
ChannelMention::setName(QJsonValue name) {
    this->name = name;
}

void
ChannelMention::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
ChannelMention::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
