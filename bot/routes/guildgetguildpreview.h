#ifndef GUILDGETGUILDPREVIEW_H
#define GUILDGETGUILDPREVIEW_H

#include "route.h"


class GuildGetGuildPreview : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/preview";

    GuildGetGuildPreview(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDPREVIEW_H
