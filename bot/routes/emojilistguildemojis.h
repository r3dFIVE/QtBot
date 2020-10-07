#ifndef EMOJILISTGUILDEMOJIS_H
#define EMOJILISTGUILDEMOJIS_H

#include "route.h"

class EmojiListGuildEmojis : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis";

    EmojiListGuildEmojis(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // EMOJILISTGUILDEMOJIS_H
