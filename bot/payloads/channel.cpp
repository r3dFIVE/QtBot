/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "channel.h"

const QString Channel::ID = "id";
const QString Channel::TYPE = "type";
const QString Channel::GUILD_ID = "guild_id";
const QString Channel::POSITION = "position";
const QString Channel::PERMISSION_OVERWRITES = "permission_overwrites" ;
const QString Channel::NAME = "name";
const QString Channel::TOPIC = "topic";
const QString Channel::NSFW = "nsfw";
const QString Channel::LAST_MESSAGE_ID = "last_message_id";
const QString Channel::BITRATE = "bitrate";
const QString Channel::USER_LIMIT = "user_limit";
const QString Channel::RATE_LIMIT_PER_USER = "rate_limit_per_user";
const QString Channel::RECIPIENTS = "recipients";
const QString Channel::ICON = "icon";
const QString Channel::OWNER_ID = "owner_id";
const QString Channel::APPLICATION_ID = "application_id";
const QString Channel::PARENT_ID = "parent_id";
const QString Channel::LAST_PIN_TIMESTAMP = "last_pin_timestamp";

QJsonValue
Channel::getId() {
    return _jsonObject[ID];
}

void
Channel::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
Channel::getType() {
    return _jsonObject[TYPE];
}

void
Channel::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
Channel::getGuildId() {
    return _jsonObject[GUILD_ID];
}

void
Channel::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonValue
Channel::getPosition() {
    return _jsonObject[POSITION];
}

void
Channel::setPosition(const QJsonValue &position) {
    _jsonObject[POSITION] = position;
}

QJsonArray
Channel::getPermissionOverwrites() {
    return _jsonObject[PERMISSION_OVERWRITES].toArray();
}

void
Channel::setPermissionOverwrites(const QJsonArray &permissionOverwrites) {
    _jsonObject[PERMISSION_OVERWRITES] = permissionOverwrites;
}

QJsonValue
Channel::getName() {
   return _jsonObject[NAME];
}

void
Channel::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
Channel::getTopic() {
    return _jsonObject[TOPIC];
}

void
Channel::setTopic(const QJsonValue &topic) {
    _jsonObject[TOPIC] = topic;
}

QJsonValue
Channel::getNsfw() {
    return _jsonObject[NSFW];
}

void
Channel::setNsfw(const QJsonValue &nsfw) {
    _jsonObject[NSFW] = nsfw;
}

QJsonValue
Channel::getLastMessageId() {
    return _jsonObject[LAST_MESSAGE_ID];
}

void
Channel::setLastMessageId(const QJsonValue &last_message_id) {
    _jsonObject[LAST_MESSAGE_ID] = last_message_id;
}

QJsonValue
Channel::getBitrate() {
    return _jsonObject[BITRATE];
}

void
Channel::setBitrate(const QJsonValue &bitrate) {
    _jsonObject[BITRATE] = bitrate;
}

QJsonValue
Channel::getUserLimit() {
    return _jsonObject[USER_LIMIT];
}

void
Channel::setUserLimit(const QJsonValue &userLimit) {
    _jsonObject[USER_LIMIT] = userLimit;
}

QJsonValue
Channel::getRateLimitPerUser() {
    return _jsonObject[RATE_LIMIT_PER_USER];
}

void
Channel::setRateLimitPerUser(const QJsonValue &rateLimitPerUser) {
    _jsonObject[RATE_LIMIT_PER_USER] = rateLimitPerUser;
}

QJsonArray
Channel::getRecipients() {
    return _jsonObject[RECIPIENTS].toArray();
}

void
Channel::setRecipients(const QJsonArray &recipients) {
     _jsonObject[RECIPIENTS] = recipients;
}

QJsonValue
Channel::getIcon() {
    return _jsonObject[ICON];
}

void
Channel::setIcon(const QJsonValue &icon) {
     _jsonObject[ICON] = icon;
}

QJsonValue
Channel::getOwnerId() {
    return _jsonObject[OWNER_ID];
}

void
Channel::setOwnerId(const QJsonValue &ownerId) {
    _jsonObject[OWNER_ID] = ownerId;
}

QJsonValue
Channel::getApplicationId() {
    return _jsonObject[APPLICATION_ID];
}

void
Channel::setApplicationId(const QJsonValue &applicationId) {
    _jsonObject[APPLICATION_ID] = applicationId;
}

QJsonValue
Channel::getParentId() {
    return _jsonObject[PARENT_ID];
}

void
Channel::setParentId(const QJsonValue &parentId) {
    _jsonObject[PARENT_ID] = parentId;
}

QJsonValue
Channel::getLastPinTimestamp() {
    return _jsonObject[LAST_PIN_TIMESTAMP];
}

void
Channel::setLastPinTimestamp(const QJsonValue &lastPinTimestamp) {
    _jsonObject[LAST_PIN_TIMESTAMP] = lastPinTimestamp;
}
