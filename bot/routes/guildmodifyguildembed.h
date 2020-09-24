#ifndef GUILDMODIFYGUILDEMBED_H
#define GUILDMODIFYGUILDEMBED_H

#include "route.h"


class GuildModifyGuildEmbed : public Route
{
public:
    GuildModifyGuildEmbed(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/embed";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDEMBED_H
