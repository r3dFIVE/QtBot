#ifndef GUILDDELETEGUILDINTEGRATION_H
#define GUILDDELETEGUILDINTEGRATION_H

#include "route.h"


class GuildDeleteGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations/{integration.id}";

    GuildDeleteGuildIntegration(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        _params[Route::INTEGRATION_ID_TOKEN] = context.getIntegrationId().toString();

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDDELETEGUILDINTEGRATION_H
