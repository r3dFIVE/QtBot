#ifndef GUILDADDGUILDMEMBERROLE_H
#define GUILDADDGUILDMEMBERROLE_H

#include "route.h"


class GuildAddGuildMemberRole : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}/roles/{role.id}";

    GuildAddGuildMemberRole(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        _pathParams[Route::ROLE_ID_TOKEN] = context.getRoleId().toString();

        buildRequest(PUT, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDADDGUILDMEMBERROLE_H
