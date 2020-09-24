#ifndef GUILDDELETEGUILDINTEGRATION_H
#define GUILDDELETEGUILDINTEGRATION_H

#include "route.h"


class GuildDeleteGuildIntegration : public Route
{
public:
    GuildDeleteGuildIntegration(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/integrations/{integration.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::INTEGRATION_ID_TOKEN, context.getIntegrationId().toString());

        buildRequest(endpoint, DELETE, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDDELETEGUILDINTEGRATION_H
