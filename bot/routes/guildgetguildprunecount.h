#ifndef GUILDGETGUILDPRUNECOUNT_H
#define GUILDGETGUILDPRUNECOUNT_H

#include "route.h"


class GuildGetGuildPruneCount : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/prune";

    GuildGetGuildPruneCount(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDGETGUILDPRUNECOUNT_H
