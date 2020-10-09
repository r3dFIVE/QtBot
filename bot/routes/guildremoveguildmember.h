#ifndef GUILDREMOVEGUILDMEMBER_H
#define GUILDREMOVEGUILDMEMBER_H

#include "route.h"


class GuildRemoveGuildMember : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}";

    GuildRemoveGuildMember(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};


#endif // GUILDREMOVEGUILDMEMBER_H
