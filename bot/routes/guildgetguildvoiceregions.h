#ifndef GUILDGETGUILDVOICEREGIONS_H
#define GUILDGETGUILDVOICEREGIONS_H

#include "route.h"


class GuildGetGuildVoiceRegions : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/regions";

    GuildGetGuildVoiceRegions(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDVOICEREGIONS_H
