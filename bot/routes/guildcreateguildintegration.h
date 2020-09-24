#ifndef GUILDCREATEGUILDINTEGRATION_H
#define GUILDCREATEGUILDINTEGRATION_H

#include "route.h"


class GuildCreateGuildIntegration : public Route
{
public:
    GuildCreateGuildIntegration(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/integrations";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, POST, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDCREATEGUILDINTEGRATION_H
