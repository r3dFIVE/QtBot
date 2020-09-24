#ifndef GUILDMODIFYCURRENTUSERNICK_H
#define GUILDMODIFYCURRENTUSERNICK_H

#include "route.h"


class GuildModifyCurrentUserNick : public Route
{
public:
    GuildModifyCurrentUserNick(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/members/@me/nick";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, PATCH, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDMODIFYCURRENTUSERNICK_H
