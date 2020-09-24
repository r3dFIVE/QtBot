#ifndef GUILDGETGUILDWIDGET_H
#define GUILDGETGUILDWIDGET_H

#include "route.h"


class GuildGetGuildWidget : public Route
{
public:
    GuildGetGuildWidget(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/widget";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDWIDGET_H
