#ifndef GUILDGETGUILDPRUNECOUNT_H
#define GUILDGETGUILDPRUNECOUNT_H

#include "route.h"


class GuildGetGuildPruneCount : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/prune";

    GuildGetGuildPruneCount(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDPRUNECOUNT_H
