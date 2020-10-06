#ifndef GUILDCREATEGUILDBAN_H
#define GUILDCREATEGUILDBAN_H

#include "route.h"


class GuildCreateGuildBan : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/bans/{user.id}";

    GuildCreateGuildBan(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDCREATEGUILDBAN_H
