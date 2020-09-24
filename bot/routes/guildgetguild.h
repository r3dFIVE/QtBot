#ifndef GUILDGETGUILD_H
#define GUILDGETGUILD_H

#include "route.h"


class GuildGetGuild : public Route
{
public:
    GuildGetGuild(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILD_H
