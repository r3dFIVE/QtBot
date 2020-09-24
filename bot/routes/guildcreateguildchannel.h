#ifndef GUILDCREATEGUILDCHANNEL_H
#define GUILDCREATEGUILDCHANNEL_H

#include "route.h"


class GuildCreateGuildChannel : public Route
{
public:
    GuildCreateGuildChannel(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/channels";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, POST, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDCREATEGUILDCHANNEL_H
