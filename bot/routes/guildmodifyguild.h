#ifndef GUILDMODIFYGUILD_H
#define GUILDMODIFYGUILD_H

#include "route.h"


class GuildModifyGuild : public Route
{
public:
    GuildModifyGuild(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILD_H
