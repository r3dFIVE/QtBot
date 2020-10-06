#ifndef GUILDCREATEGUILD_H
#define GUILDCREATEGUILD_H

#include "route.h"
#include "bucket.h"

class GuildCreateGuild : public Route
{
public:
    const QString PATH = "/guilds";

    GuildCreateGuild(const EventContext &context) {
        buildRequest(POST, PATH, GLOBAL_BUCKET, context.getTargetPayload());
    }
};

#endif // GUILDCREATEGUILD_H
