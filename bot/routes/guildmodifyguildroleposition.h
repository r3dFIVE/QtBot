#ifndef GUILDMODIFYGUILDROLEPOSITION_H
#define GUILDMODIFYGUILDROLEPOSITION_H

#include "route.h"


class GuildModifyGuildRolePosition : public Route
{
public:
    GuildModifyGuildRolePosition(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/roles";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDROLEPOSITION_H
