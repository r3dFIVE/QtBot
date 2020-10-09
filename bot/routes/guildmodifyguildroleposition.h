#ifndef GUILDMODIFYGUILDROLEPOSITION_H
#define GUILDMODIFYGUILDROLEPOSITION_H

#include "route.h"


class GuildModifyGuildRolePosition : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles";

    GuildModifyGuildRolePosition(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDROLEPOSITION_H
