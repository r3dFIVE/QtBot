#ifndef GUILDBEGINGUILDPRUNE_H
#define GUILDBEGINGUILDPRUNE_H

#include "route.h"


class GuildBeginGuildPrune : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/prune";

    GuildBeginGuildPrune(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(POST, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDBEGINGUILDPRUNE_H
