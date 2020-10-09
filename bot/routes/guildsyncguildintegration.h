#ifndef GUILDSYNCGUILDINTEGRATION_H
#define GUILDSYNCGUILDINTEGRATION_H

#include "route.h"


class GuildSyncGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations/{integration.id}";

    GuildSyncGuildIntegration(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::INTEGRATION_ID_TOKEN] = context.getIntegrationId().toString();

        buildRequest(POST, PATH, _pathParams[Route::INTEGRATION_ID_TOKEN]);
    }
};

#endif // GUILDSYNCGUILDINTEGRATION_H
