#ifndef GUILDADDGUILDMEMBER_H
#define GUILDADDGUILDMEMBER_H

#include "discordapi.h"
#include "route.h"


class GuildAddGuildMember : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}";

    GuildAddGuildMember(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // GUILDADDGUILDMEMBER_H
