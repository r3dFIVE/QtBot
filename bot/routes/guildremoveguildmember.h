#ifndef GUILDREMOVEGUILDMEMBER_H
#define GUILDREMOVEGUILDMEMBER_H

#include "route.h"


class GuildRemoveGuildMember : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}";

    GuildRemoveGuildMember(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};


#endif // GUILDREMOVEGUILDMEMBER_H
