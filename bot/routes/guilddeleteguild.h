#ifndef GUILDDELETEGUILD_H
#define GUILDDELETEGUILD_H

#include "route.h"


class GuildDeleteGuild : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}";

    GuildDeleteGuild(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _params[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // GUILDDELETEGUILD_H
