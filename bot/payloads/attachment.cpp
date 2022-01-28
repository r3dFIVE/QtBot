/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "attachment.h"

const QString Attachment::DESCRIPTION = "description";
const QString Attachment::CONTENT_TYPE = "content_type";
const QString Attachment::CHECKSUM = "checksum";
const QString Attachment::ID = "id";
const QString Attachment::FILENAME = "filename";
const QString Attachment::SIZE = "size";
const QString Attachment::URL = "url";
const QString Attachment::PROXY_URL = "proxy_url";
const QString Attachment::HEIGHT = "height";
const QString Attachment::WIDTH = "width";
const QString Attachment::MESSAGE_ID = "message_id";
const QString Attachment::CHANNEL_ID = "channel_id";
const QString Attachment::GUILD_ID = "guild_id";
const QString Attachment::USER_ID = "user_id";

QJsonValue
Attachment::getDescription() const {
    return _jsonObject[DESCRIPTION];
}

void
Attachment::setDescription(const QJsonValue &description) {
    _jsonObject[DESCRIPTION] = description;
}

QJsonValue
Attachment::getContentType() const {
    return _jsonObject[CONTENT_TYPE];
}

void
Attachment::setContentType(const QJsonValue &contentType) {
    _jsonObject[CONTENT_TYPE] = contentType;
}

QJsonValue
Attachment::getChecksum() const {
    return _jsonObject[CHECKSUM];
}

void
Attachment::setChecksum(const QJsonValue &checksum) {
    _jsonObject[CHECKSUM] = checksum;
}

QJsonValue
Attachment::getId() const {
    return _jsonObject[ID];
}

void
Attachment::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
Attachment::getFilename() const {
    return _jsonObject[FILENAME];
}

void
Attachment::setFilename(const QJsonValue &filename) {
    _jsonObject[FILENAME] = filename;
}

QJsonValue
Attachment::getSize() const {
    return _jsonObject[SIZE];
}

void
Attachment::setSize(const QJsonValue &size) {
    _jsonObject[SIZE] = size;
}

QJsonValue
Attachment::getUrl() const {
    return _jsonObject[URL];
}

void
Attachment::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
Attachment::getProxyUrl() const {
    return _jsonObject[PROXY_URL];
}

void
Attachment::setProxyUrl(const QJsonValue &proxy_url) {
    _jsonObject[PROXY_URL] = proxy_url;
}

QJsonValue
Attachment::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
Attachment::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
Attachment::getWidth() const {
    return _jsonObject[WIDTH];
}

void
Attachment::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}

QJsonValue
Attachment::getMessageId() const {
    return _jsonObject[MESSAGE_ID];
}

void
Attachment::setMessageId(const QJsonValue &messageId) {
    _jsonObject[MESSAGE_ID] = messageId;
}

QJsonValue
Attachment::getUserId() const {
    return _jsonObject[USER_ID];
}

void
Attachment::setUserId(const QJsonValue &userId) {
    _jsonObject[USER_ID] = userId;
}

QJsonValue
Attachment::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
Attachment::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonValue
Attachment::getChannelId() const {
    return _jsonObject[CHANNEL_ID];
}

void
Attachment::setChannelId(const QJsonValue &channelId) {
    _jsonObject[CHANNEL_ID] = channelId;
}
