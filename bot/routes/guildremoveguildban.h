#ifndef GUILDREMOVEGUILDBAN_H
#define GUILDREMOVEGUILDBAN_H

#include "route.h"


class GuildRemoveGuildBan : public Route
{
public:
    GuildRemoveGuildBan(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/bans/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, DELETE, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDREMOVEGUILDBAN_H
