#ifndef GUILDCREATEGUILDINTEGRATION_H
#define GUILDCREATEGUILDINTEGRATION_H

#include "route.h"


class GuildCreateGuildIntegration : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations";

    GuildCreateGuildIntegration(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(POST, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDCREATEGUILDINTEGRATION_H
