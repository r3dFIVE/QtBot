#ifndef GUILDCREATEGUILDROLE_H
#define GUILDCREATEGUILDROLE_H

#include "route.h"


class GuildCreateGuildRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles";

    GuildCreateGuildRole(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(POST, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDCREATEGUILDROLE_H
