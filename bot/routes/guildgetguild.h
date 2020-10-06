#ifndef GUILDGETGUILD_H
#define GUILDGETGUILD_H

#include "route.h"


class GuildGetGuild : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}";

    GuildGetGuild(const EventContext &context) {        
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILD_H
