#ifndef GUILDBEGINGUILDPRUNE_H
#define GUILDBEGINGUILDPRUNE_H

#include "route.h"


class GuildBeginGuildPrune : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/prune";

    GuildBeginGuildPrune(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(POST, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDBEGINGUILDPRUNE_H
