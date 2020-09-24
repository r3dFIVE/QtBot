#ifndef GUILDGETGUILDEMBED_H
#define GUILDGETGUILDEMBED_H

#include "route.h"


class GuildGetGuildEmbed : public Route
{
public:
    GuildGetGuildEmbed(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/embed";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDEMBED_H
