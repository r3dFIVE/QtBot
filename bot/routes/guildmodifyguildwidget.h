#ifndef GUILDMODIFYGUILDWIDGET_H
#define GUILDMODIFYGUILDWIDGET_H

#include "route.h"


class GuildModifyGuildWidget : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget";

    GuildModifyGuildWidget(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYGUILDWIDGET_H
