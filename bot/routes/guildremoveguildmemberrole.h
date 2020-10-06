#ifndef GUILDREMOVEGUILDMEMBERROLE_H
#define GUILDREMOVEGUILDMEMBERROLE_H

#include "route.h"


class GuildRemoveGuildMemberRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}/roles/{role.id}";

    GuildRemoveGuildMemberRole(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        _params[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDREMOVEGUILDMEMBERROLE_H
