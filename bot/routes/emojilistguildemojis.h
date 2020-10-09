#ifndef EMOJILISTGUILDEMOJIS_H
#define EMOJILISTGUILDEMOJIS_H

#include "route.h"

class EmojiListGuildEmojis : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis";

    EmojiListGuildEmojis(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(GET, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // EMOJILISTGUILDEMOJIS_H
