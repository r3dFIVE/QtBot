#ifndef GUILDMODIFYGUILDWIDGET_H
#define GUILDMODIFYGUILDWIDGET_H

#include "route.h"


class GuildModifyGuildWidget : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget";

    GuildModifyGuildWidget(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDWIDGET_H
