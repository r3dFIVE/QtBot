#ifndef GUILDGETGUILDINVITES_H
#define GUILDGETGUILDINVITES_H

#include "route.h"


class GuildGetGuildInvites : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/invites";

    GuildGetGuildInvites(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDGETGUILDINVITES_H
