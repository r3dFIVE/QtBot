#ifndef GUILDDELETEGUILDROLE_H
#define GUILDDELETEGUILDROLE_H

#include "route.h"


class GuildDeleteGuildRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles/{role.id}";

    GuildDeleteGuildRole(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDDELETEGUILDROLE_H
