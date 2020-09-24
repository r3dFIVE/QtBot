#ifndef GUILDGETGUILDMEMEBER_H
#define GUILDGETGUILDMEMEBER_H

#include "route.h"


class GuildGetGuildMember : public Route
{
public:
    GuildGetGuildMember(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/members/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDMEMEBER_H
