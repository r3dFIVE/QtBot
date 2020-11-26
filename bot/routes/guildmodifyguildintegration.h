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

#ifndef GUILDMODIFYGUILDINTEGRATION_H
#define GUILDMODIFYGUILDINTEGRATION_H

#include "route.h"


class GuildModifyGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations/{integration.id}";

    GuildModifyGuildIntegration(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::INTEGRATION_ID_TOKEN] = context.getIntegrationId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDINTEGRATION_H
