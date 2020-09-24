#ifndef GUILDGETGUILDINVITES_H
#define GUILDGETGUILDINVITES_H

#include "route.h"


class GuildGetGuildInvites : public Route
{
public:
    GuildGetGuildInvites(const EventContext &context) {
        QString endpoint = "/guilds/{guild.id}/invites";

        endpoint.replace(Route::GUILD_ID_TOKEN, context.getGuildId().toString());

        buildRequest(endpoint, GET, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDGETGUILDINVITES_H
