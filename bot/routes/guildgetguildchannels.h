#ifndef GUILDGETGUILDCHANNELS_H
#define GUILDGETGUILDCHANNELS_H

#include "route.h"


class GuildGetGuildChannels : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/channels";

    GuildGetGuildChannels(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDCHANNELS_H
