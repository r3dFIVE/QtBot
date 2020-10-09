#ifndef GUILDGETGUILDWIDGET_H
#define GUILDGETGUILDWIDGET_H

#include "route.h"


class GuildGetGuildWidget : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget.json";

    GuildGetGuildWidget(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDWIDGET_H
