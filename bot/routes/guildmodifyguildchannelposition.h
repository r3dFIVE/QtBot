#ifndef GUILDMODIFYGUILDCHANNELPOSITION_H
#define GUILDMODIFYGUILDCHANNELPOSITION_H

#include "route.h"


class GuildModifyGuildChannelPosition : public Route
{
public:
    GuildModifyGuildChannelPosition(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/channels";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDCHANNELPOSITION_H
