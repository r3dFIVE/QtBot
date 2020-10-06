#ifndef GUILDCREATEGUILDINTEGRATION_H
#define GUILDCREATEGUILDINTEGRATION_H

#include "route.h"


class GuildCreateGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations";

    GuildCreateGuildIntegration(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(POST, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDCREATEGUILDINTEGRATION_H
