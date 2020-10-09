#ifndef GUILDCREATEGUILDBAN_H
#define GUILDCREATEGUILDBAN_H

#include "route.h"


class GuildCreateGuildBan : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/bans/{user.id}";

    GuildCreateGuildBan(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDCREATEGUILDBAN_H
