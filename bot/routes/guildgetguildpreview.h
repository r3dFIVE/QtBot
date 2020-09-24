#ifndef GUILDGETGUILDPREVIEW_H
#define GUILDGETGUILDPREVIEW_H

#include "route.h"


class GuildGetGuildPreview : public Route
{
public:
    GuildGetGuildPreview(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/preview";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDPREVIEW_H
