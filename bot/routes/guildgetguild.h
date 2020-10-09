#ifndef GUILDGETGUILD_H
#define GUILDGETGUILD_H

#include "route.h"


class GuildGetGuild : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}";

    GuildGetGuild(const EventContext &context) {        
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDGETGUILD_H
