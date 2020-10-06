#ifndef GUILDCREATEGUILDCHANNEL_H
#define GUILDCREATEGUILDCHANNEL_H

#include "route.h"


class GuildCreateGuildChannel : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/channels";

    GuildCreateGuildChannel(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(POST, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDCREATEGUILDCHANNEL_H
