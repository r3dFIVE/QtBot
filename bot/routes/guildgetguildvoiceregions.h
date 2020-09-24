#ifndef GUILDGETGUILDVOICEREGIONS_H
#define GUILDGETGUILDVOICEREGIONS_H

#include "route.h"


class GuildGetGuildVoiceRegions : public Route
{
public:
    GuildGetGuildVoiceRegions(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/regions";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDVOICEREGIONS_H
