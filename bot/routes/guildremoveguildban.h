#ifndef GUILDREMOVEGUILDBAN_H
#define GUILDREMOVEGUILDBAN_H

#include "route.h"


class GuildRemoveGuildBan : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/bans/{user.id}";

    GuildRemoveGuildBan(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDREMOVEGUILDBAN_H
