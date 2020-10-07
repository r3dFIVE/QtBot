#ifndef GUILDGETGUILDEMBED_H
#define GUILDGETGUILDEMBED_H

#include "route.h"


class GuildGetGuildEmbed : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/embed";

    GuildGetGuildEmbed(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDEMBED_H
