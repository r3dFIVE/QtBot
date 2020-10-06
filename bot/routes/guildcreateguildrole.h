#ifndef GUILDCREATEGUILDROLE_H
#define GUILDCREATEGUILDROLE_H

#include "route.h"


class GuildCreateGuildRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles";

    GuildCreateGuildRole(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(POST, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDCREATEGUILDROLE_H
