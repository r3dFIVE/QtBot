#ifndef GUILDCREATEGUILDCHANNEL_H
#define GUILDCREATEGUILDCHANNEL_H

#include "route.h"


class GuildCreateGuildChannel : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/channels";

    GuildCreateGuildChannel(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(POST, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDCREATEGUILDCHANNEL_H
