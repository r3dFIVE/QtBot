#ifndef GUILDGETGUILDROLES_H
#define GUILDGETGUILDROLES_H

#include "route.h"


class GuildGetGuildRoles : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/roles";

    GuildGetGuildRoles(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDROLES_H
