#ifndef GUILDMODIFYGUILDCHANNELPOSITION_H
#define GUILDMODIFYGUILDCHANNELPOSITION_H

#include "route.h"


class GuildModifyGuildChannelPosition : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/channels";

    GuildModifyGuildChannelPosition(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILDCHANNELPOSITION_H
