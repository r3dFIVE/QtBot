#ifndef GUILDMODIFYGUILDROLE_H
#define GUILDMODIFYGUILDROLE_H

#include "route.h"


class GuildModifyGuildRole : public Route
{
public:
    GuildModifyGuildRole(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/roles/{role.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::ROLE_ID_TOKEN, context.getRoleId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDROLE_H
