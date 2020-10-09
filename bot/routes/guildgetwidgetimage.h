#ifndef GUILDGETWIDGETIMAGE_H
#define GUILDGETWIDGETIMAGE_H

#include "route.h"


class GuildGetWidgetImage : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget.png";

    GuildGetWidgetImage(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDGETWIDGETIMAGE_H
