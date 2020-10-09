#ifndef GUILDMODIFYGUILD_H
#define GUILDMODIFYGUILD_H

#include "route.h"


class GuildModifyGuild : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}";

    GuildModifyGuild(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILD_H
