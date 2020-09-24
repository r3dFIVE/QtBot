#ifndef GUILDSYNCGUILDINTEGRATION_H
#define GUILDSYNCGUILDINTEGRATION_H

#include "route.h"


class GuildSyncGuildIntegration : public Route
{
public:
    GuildSyncGuildIntegration(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/integrations/{integration.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::INTEGRATION_ID_TOKEN, context.getIntegrationId().toString());

        buildRequest(endpoint, POST, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDSYNCGUILDINTEGRATION_H
