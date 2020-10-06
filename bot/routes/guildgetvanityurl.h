#ifndef GUILDGETVANITYURL_H
#define GUILDGETVANITYURL_H

#include "route.h"


class GuildGetVanityUrl : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/vanity-url";

    GuildGetVanityUrl(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETVANITYURL_H
