#ifndef GUILDREMOVEGUILDBAN_H
#define GUILDREMOVEGUILDBAN_H

#include "route.h"


class GuildRemoveGuildBan : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/bans/{user.id}";

    GuildRemoveGuildBan(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDREMOVEGUILDBAN_H
