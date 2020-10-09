#ifndef GUILDGETGUILDBAN_H
#define GUILDGETGUILDBAN_H

#include "route.h"


class GuildGetGuildBan : public Route
{
public:
   const QString PATH = "/guilds/{guild.id}/bans/{user.id}";

    GuildGetGuildBan(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDBAN_H
