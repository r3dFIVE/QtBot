#ifndef GUILDDELETEGUILD_H
#define GUILDDELETEGUILD_H

#include "route.h"


class GuildDeleteGuild : public Route
{
public:
    GuildDeleteGuild(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, DELETE, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDDELETEGUILD_H
