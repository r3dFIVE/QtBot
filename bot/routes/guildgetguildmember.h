#ifndef GUILDGETGUILDMEMEBER_H
#define GUILDGETGUILDMEMEBER_H

#include "route.h"


class GuildGetGuildMember : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/members/{user.id}";

    GuildGetGuildMember(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDMEMEBER_H
