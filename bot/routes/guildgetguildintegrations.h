#ifndef GUILDGETGUILDINTEGRATIONS_H
#define GUILDGETGUILDINTEGRATIONS_H

#include "route.h"


class GuildGetGuildIntegrations : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/integrations";

    GuildGetGuildIntegrations(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDINTEGRATIONS_H
