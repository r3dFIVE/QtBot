#ifndef GUILDMODIFYGUILD_H
#define GUILDMODIFYGUILD_H

#include "route.h"


class GuildModifyGuild : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}";

    GuildModifyGuild(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILD_H
