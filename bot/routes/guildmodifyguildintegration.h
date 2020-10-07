#ifndef GUILDMODIFYGUILDINTEGRATION_H
#define GUILDMODIFYGUILDINTEGRATION_H

#include "route.h"


class GuildModifyGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations/{integration.id}";

    GuildModifyGuildIntegration(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::INTEGRATION_ID_TOKEN] = context.getIntegrationId().toString();

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILDINTEGRATION_H
