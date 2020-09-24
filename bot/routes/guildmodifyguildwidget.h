#ifndef GUILDMODIFYGUILDWIDGET_H
#define GUILDMODIFYGUILDWIDGET_H

#include "route.h"


class GuildModifyGuildWidget : public Route
{
public:
    GuildModifyGuildWidget(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/widget";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYGUILDWIDGET_H
