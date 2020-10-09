#ifndef GUILDMODIFYGUILDMEMBER_H
#define GUILDMODIFYGUILDMEMBER_H

#include "route.h"


class GuildModifyGuildMember : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}";

    GuildModifyGuildMember(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDMODIFYGUILDMEMBER_H
