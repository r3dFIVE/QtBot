#ifndef GUILDCREATEGUILDBAN_H
#define GUILDCREATEGUILDBAN_H

#include "route.h"


class GuildCreateGuildBan : public Route
{
public:
    GuildCreateGuildBan(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/bans/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, PUT, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDCREATEGUILDBAN_H
