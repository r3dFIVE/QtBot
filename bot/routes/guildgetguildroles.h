#ifndef GUILDGETGUILDROLES_H
#define GUILDGETGUILDROLES_H

#include "route.h"


class GuildGetGuildRoles : public Route
{
public:
    GuildGetGuildRoles(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/roles";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDROLES_H
