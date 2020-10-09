#ifndef USERLEAVEGUILD_H
#define USERLEAVEGUILD_H

#include "route.h"


class UserLeaveGuild : public Route
{
public:
    const QString PATH = "/users/@me/guilds/{guild.id}";

    UserLeaveGuild(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // USERLEAVEGUILD_H
