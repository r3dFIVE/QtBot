#ifndef GUILDGETGUILDBANS_H
#define GUILDGETGUILDBANS_H

#include "route.h"


class GuildGetGuildBans : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/bans";

    GuildGetGuildBans(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDBANS_H
