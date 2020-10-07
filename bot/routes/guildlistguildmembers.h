#ifndef GUILDLISTGUILDMEMBERS_H
#define GUILDLISTGUILDMEMBERS_H

#include "route.h"


class GuildListGuildMembers : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members";

    GuildListGuildMembers(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload(), context.getQueryParams());
    }
};

#endif // GUILDLISTGUILDMEMBERS_H
