#ifndef GUILDGETGUILDVOICEREGIONS_H
#define GUILDGETGUILDVOICEREGIONS_H

#include "route.h"


class GuildGetGuildVoiceRegions : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/regions";

    GuildGetGuildVoiceRegions(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDVOICEREGIONS_H
