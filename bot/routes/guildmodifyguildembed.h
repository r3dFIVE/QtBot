#ifndef GUILDMODIFYGUILDEMBED_H
#define GUILDMODIFYGUILDEMBED_H

#include "route.h"


class GuildModifyGuildEmbed : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/embed";

    GuildModifyGuildEmbed(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILDEMBED_H
