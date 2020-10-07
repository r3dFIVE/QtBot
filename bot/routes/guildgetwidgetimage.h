#ifndef GUILDGETWIDGETIMAGE_H
#define GUILDGETWIDGETIMAGE_H

#include "route.h"


class GuildGetWidgetImage : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget.png";

    GuildGetWidgetImage(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload(), context.getQueryParams());
    }
};

#endif // GUILDGETWIDGETIMAGE_H
