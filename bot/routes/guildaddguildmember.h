#ifndef GUILDADDGUILDMEMBER_H
#define GUILDADDGUILDMEMBER_H

#include "discordapi.h"
#include "route.h"


class GuildAddGuildMember : public Route
{
public:
    GuildAddGuildMember(EventContext context) {
        QString endpoint = "/guilds/{guild.id}/members/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, PUT, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDADDGUILDMEMBER_H
