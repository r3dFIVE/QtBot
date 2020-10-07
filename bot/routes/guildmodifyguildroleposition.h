#ifndef GUILDMODIFYGUILDROLEPOSITION_H
#define GUILDMODIFYGUILDROLEPOSITION_H

#include "route.h"


class GuildModifyGuildRolePosition : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles";

    GuildModifyGuildRolePosition(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILDROLEPOSITION_H
