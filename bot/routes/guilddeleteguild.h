#ifndef GUILDDELETEGUILD_H
#define GUILDDELETEGUILD_H

#include "route.h"


class GuildDeleteGuild : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}";

    GuildDeleteGuild(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // GUILDDELETEGUILD_H
