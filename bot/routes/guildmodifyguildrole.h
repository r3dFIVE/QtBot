#ifndef GUILDMODIFYGUILDROLE_H
#define GUILDMODIFYGUILDROLE_H

#include "route.h"


class GuildModifyGuildRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles/{role.id}";

    GuildModifyGuildRole(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILDROLE_H
