#ifndef GUILDGETGUILDBAN_H
#define GUILDGETGUILDBAN_H

#include "route.h"


class GuildGetGuildBan : public Route
{
public:
   const QString PATH = "/guilds/{guild.id}/bans/{user.id}";

    GuildGetGuildBan(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDBAN_H
