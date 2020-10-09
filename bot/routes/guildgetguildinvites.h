#ifndef GUILDGETGUILDINVITES_H
#define GUILDGETGUILDINVITES_H

#include "route.h"


class GuildGetGuildInvites : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/invites";

    GuildGetGuildInvites(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDGETGUILDINVITES_H
