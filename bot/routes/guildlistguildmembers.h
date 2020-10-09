#ifndef GUILDLISTGUILDMEMBERS_H
#define GUILDLISTGUILDMEMBERS_H

#include "route.h"


class GuildListGuildMembers : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members";

    GuildListGuildMembers(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDLISTGUILDMEMBERS_H
