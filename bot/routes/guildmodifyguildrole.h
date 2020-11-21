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

#ifndef GUILDMODIFYGUILDROLE_H
#define GUILDMODIFYGUILDROLE_H

#include "route.h"


class GuildModifyGuildRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles/{role.id}";

    GuildModifyGuildRole(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDROLE_H
