#ifndef GUILDREMOVEGUILDMEMBER_H
#define GUILDREMOVEGUILDMEMBER_H

#include "route.h"


class GuildRemoveGuildMember : public Route
{
public:
    GuildRemoveGuildMember(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/members/{user.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, DELETE, GUILD_ID_BUCKET, context);
    }
};


#endif // GUILDREMOVEGUILDMEMBER_H
