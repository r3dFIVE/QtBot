#ifndef GUILDCREATEGUILDROLE_H
#define GUILDCREATEGUILDROLE_H

#include "route.h"


class GuildCreateGuildRole : public Route
{
public:
    GuildCreateGuildRole(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/roles";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, POST, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDCREATEGUILDROLE_H
