#ifndef GUILDMODIFYGUILDINTEGRATION_H
#define GUILDMODIFYGUILDINTEGRATION_H

#include "route.h"


class GuildModifyGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations/{integration.id}";

    GuildModifyGuildIntegration(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::INTEGRATION_ID_TOKEN] = context.getIntegrationId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDINTEGRATION_H
