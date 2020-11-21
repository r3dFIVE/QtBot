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

