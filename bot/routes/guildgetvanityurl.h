#ifndef GUILDGETVANITYURL_H
#define GUILDGETVANITYURL_H

#include "route.h"


class GuildGetVanityUrl : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/vanity-url";

    GuildGetVanityUrl(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETVANITYURL_H
