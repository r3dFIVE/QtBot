#ifndef GUILDMODIFYGUILDCHANNELPOSITION_H
#define GUILDMODIFYGUILDCHANNELPOSITION_H

#include "route.h"


class GuildModifyGuildChannelPosition : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/channels";

    GuildModifyGuildChannelPosition(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDCHANNELPOSITION_H
