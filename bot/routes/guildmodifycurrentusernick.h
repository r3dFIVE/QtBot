#ifndef GUILDMODIFYCURRENTUSERNICK_H
#define GUILDMODIFYCURRENTUSERNICK_H

#include "route.h"


class GuildModifyCurrentUserNick : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/@me/nick";

    GuildModifyCurrentUserNick(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDMODIFYCURRENTUSERNICK_H
