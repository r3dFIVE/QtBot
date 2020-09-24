#ifndef GUILDGETGUILDPRUNECOUNT_H
#define GUILDGETGUILDPRUNECOUNT_H

#include "route.h"


class GuildGetGuildPruneCount : public Route
{
public:
    GuildGetGuildPruneCount(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/prune";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDPRUNECOUNT_H
