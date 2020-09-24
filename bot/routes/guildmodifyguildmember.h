#ifndef GUILDMODIFYGUILDMEMBER_H
#define GUILDMODIFYGUILDMEMBER_H

#include "route.h"


class GuildModifyGuildMember : public Route
{
public:
    GuildModifyGuildMember(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/members/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDMEMBER_H
