#ifndef GUILDADDGUILDMEMBER_H
#define GUILDADDGUILDMEMBER_H

#include "discordapi.h"
#include "route.h"


class GuildAddGuildMember : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}";

    GuildAddGuildMember(EventContext context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDADDGUILDMEMBER_H
