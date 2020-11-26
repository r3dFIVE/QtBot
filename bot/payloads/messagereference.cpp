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
