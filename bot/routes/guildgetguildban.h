#ifndef GUILDGETGUILDBAN_H
#define GUILDGETGUILDBAN_H

#include "route.h"


class GuildGetGuildBan : public Route
{
public:
    GuildGetGuildBan(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/bans/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDBAN_H
