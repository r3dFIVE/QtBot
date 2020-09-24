#ifndef GUILDMODIFYGUILDINTEGRATION_H
#define GUILDMODIFYGUILDINTEGRATION_H

#include "route.h"


class GuildModifyGuildIntegration : public Route
{
public:
    GuildModifyGuildIntegration(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/integrations/{integration.id}";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        endpoint.replace(Route::INTEGRATION_ID_TOKEN, context.getIntegrationId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDINTEGRATION_H
