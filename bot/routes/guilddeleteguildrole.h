#ifndef GUILDDELETEGUILDROLE_H
#define GUILDDELETEGUILDROLE_H

#include "route.h"


class GuildDeleteGuildRole : public Route
{
public:
    GuildDeleteGuildRole(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/roles/{role.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::ROLE_ID_TOKEN, context.getRoleId().toString());

        buildRequest(endpoint, DELETE, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDDELETEGUILDROLE_H
