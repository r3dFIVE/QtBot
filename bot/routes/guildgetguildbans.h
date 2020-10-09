#ifndef GUILDGETGUILDBANS_H
#define GUILDGETGUILDBANS_H

#include "route.h"


class GuildGetGuildBans : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/bans";

    GuildGetGuildBans(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDBANS_H
