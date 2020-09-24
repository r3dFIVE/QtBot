#ifndef GUILDADDGUILDMEMBERROLE_H
#define GUILDADDGUILDMEMBERROLE_H

#include "route.h"


class GuildAddGuildMemberRole : public Route
{
public:
    GuildAddGuildMemberRole(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/members/{user.id}/roles/{role.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        endpoint.replace(Route::ROLE_ID_TOKEN, context.getRoleId().toString());

        buildRequest(endpoint, PUT, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDADDGUILDMEMBERROLE_H
