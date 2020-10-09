#ifndef GUILDGETGUILDPREVIEW_H
#define GUILDGETGUILDPREVIEW_H

#include "route.h"


class GuildGetGuildPreview : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/preview";

    GuildGetGuildPreview(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDPREVIEW_H
