#ifndef GUILDGETWIDGETIMAGE_H
#define GUILDGETWIDGETIMAGE_H

#include "route.h"


class GuildGetWidgetImage : public Route
{
public:
    GuildGetWidgetImage(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/widget.png";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETWIDGETIMAGE_H
