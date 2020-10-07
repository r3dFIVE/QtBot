#ifndef GUILDGETGUILDCHANNELS_H
#define GUILDGETGUILDCHANNELS_H

#include "route.h"


class GuildGetGuildChannels : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/channels";

    GuildGetGuildChannels(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDCHANNELS_H
