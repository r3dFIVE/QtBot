#ifndef GUILDGETGUILDROLES_H
#define GUILDGETGUILDROLES_H

#include "route.h"


class GuildGetGuildRoles : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles";

    GuildGetGuildRoles(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDROLES_H
