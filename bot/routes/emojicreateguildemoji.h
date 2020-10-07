#ifndef EMOJICREATEGUILDEMOJI_H
#define EMOJICREATEGUILDEMOJI_H

#include "route.h"


class EmojiCreateGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis";

    EmojiCreateGuildEmoji(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(POST, PATH, guildId, context.getTargetPayload());
    }
};

#endif // EMOJICREATEGUILDEMOJI_H
