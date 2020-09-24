#ifndef GUILDGETGUILDINTEGRATIONS_H
#define GUILDGETGUILDINTEGRATIONS_H

#include "route.h"


class GuildGetGuildIntegrations : public Route
{
public:
    GuildGetGuildIntegrations(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/integrations";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDINTEGRATIONS_H
