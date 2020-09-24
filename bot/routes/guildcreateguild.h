#ifndef GUILDCREATEGUILD_H
#define GUILDCREATEGUILD_H

#include "route.h"


class GuildCreateGuild : public Route
{
public:
    GuildCreateGuild(const EventContext &context) {
        QString endpoint = "/guilds";

        buildRequest(endpoint, POST, GUILD_ID_BUCKET, context);
    }
};

#endif // GUILDCREATEGUILD_H
