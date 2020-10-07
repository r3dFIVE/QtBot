#ifndef USERLEAVEGUILD_H
#define USERLEAVEGUILD_H

#include "route.h"


class UserLeaveGuild : public Route
{
public:
    const QString PATH = "/users/@me/guilds/{guild.id}";

    UserLeaveGuild(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // USERLEAVEGUILD_H
