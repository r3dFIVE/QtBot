#ifndef GUILDMODIFYCURRENTUSERNICK_H
#define GUILDMODIFYCURRENTUSERNICK_H

#include "route.h"


class GuildModifyCurrentUserNick : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/@me/nick";

    GuildModifyCurrentUserNick(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYCURRENTUSERNICK_H
