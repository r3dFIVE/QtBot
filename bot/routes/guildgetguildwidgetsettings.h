#ifndef GUILDGETGUILDWIDGETSETTINGS_H
#define GUILDGETGUILDWIDGETSETTINGS_H

#include "route.h"


class GuildGetGuildWidgetSettings : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/widget";

    GuildGetGuildWidgetSettings(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDWIDGETSETTINGS_H
