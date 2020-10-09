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
