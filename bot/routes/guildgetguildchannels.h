#ifndef GUILDGETGUILDCHANNELS_H
#define GUILDGETGUILDCHANNELS_H

#include "route.h"


class GuildGetGuildChannels : public Route
{
public:
    GuildGetGuildChannels(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/channels";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDCHANNELS_H
