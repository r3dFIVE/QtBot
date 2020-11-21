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

#include "guildroledelete.h"


const QString GuildRoleDelete::GUILD_ID = "guild_id";
const QString GuildRoleDelete::ROLE_ID = "role_id";

QJsonValue
GuildRoleDelete::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
GuildRoleDelete::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}


QJsonValue
GuildRoleDelete::getRoleId() const {
    return _jsonObject[ROLE_ID];
}

void
GuildRoleDelete::setRoleId(const QJsonValue &roleId) {
    _jsonObject[ROLE_ID] = roleId;
}
