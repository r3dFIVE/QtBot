#ifndef GUILDGETGUILDBANS_H
#define GUILDGETGUILDBANS_H

#include "route.h"


class GuildGetGuildBans : public Route
{
public:
    GuildGetGuildBans(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/bans";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDBANS_H
