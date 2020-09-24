#ifndef GUILDBEGINGUILDPRUNE_H
#define GUILDBEGINGUILDPRUNE_H

#include "route.h"


class GuildBeginGuildPrune : public Route
{
public:
    GuildBeginGuildPrune(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/prune";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, POST, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDBEGINGUILDPRUNE_H
