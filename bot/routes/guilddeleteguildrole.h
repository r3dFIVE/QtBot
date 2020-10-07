#ifndef GUILDDELETEGUILDROLE_H
#define GUILDDELETEGUILDROLE_H

#include "route.h"


class GuildDeleteGuildRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles/{role.id}";

    GuildDeleteGuildRole(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDDELETEGUILDROLE_H
