#ifndef GUILDGETGUILDWIDGET_H
#define GUILDGETGUILDWIDGET_H

#include "route.h"


class GuildGetGuildWidget : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget";

    GuildGetGuildWidget(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDWIDGET_H
