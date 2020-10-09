#ifndef GUILDDELETEGUILDINTEGRATION_H
#define GUILDDELETEGUILDINTEGRATION_H

#include "route.h"


class GuildDeleteGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations/{integration.id}";

    GuildDeleteGuildIntegration(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::INTEGRATION_ID_TOKEN] = context.getIntegrationId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::INTEGRATION_ID_TOKEN], context);
    }
};

#endif // GUILDDELETEGUILDINTEGRATION_H
