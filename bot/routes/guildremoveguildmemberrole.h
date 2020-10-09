#ifndef GUILDREMOVEGUILDMEMBERROLE_H
#define GUILDREMOVEGUILDMEMBERROLE_H

#include "route.h"


class GuildRemoveGuildMemberRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}/roles/{role.id}";

    GuildRemoveGuildMemberRole(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        _pathParams[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDREMOVEGUILDMEMBERROLE_H
