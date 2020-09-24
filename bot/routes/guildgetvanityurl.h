#ifndef GUILDGETVANITYURL_H
#define GUILDGETVANITYURL_H

#include "route.h"


class GuildGetVanityUrl : public Route
{
public:
    GuildGetVanityUrl(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/vanity-url";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETVANITYURL_H
