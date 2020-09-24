#ifndef GUILDLISTGUILDMEMBERS_H
#define GUILDLISTGUILDMEMBERS_H

#include "route.h"


class GuildListGuildMembers : public Route
{
public:
    GuildListGuildMembers(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/members";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDLISTGUILDMEMBERS_H
