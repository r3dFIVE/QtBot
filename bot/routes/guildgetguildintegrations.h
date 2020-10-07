#ifndef GUILDGETGUILDINTEGRATIONS_H
#define GUILDGETGUILDINTEGRATIONS_H

#include "route.h"


class GuildGetGuildIntegrations : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations";

    GuildGetGuildIntegrations(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDINTEGRATIONS_H
