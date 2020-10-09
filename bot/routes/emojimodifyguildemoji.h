#ifndef EMOJIMODIFYGUILDEMOJI_H
#define EMOJIMODIFYGUILDEMOJI_H

#include "route.h"


class EmojiModifyGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis/{emoji.id}";

    EmojiModifyGuildEmoji(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // EMOJIMODIFYGUILDEMOJI_H
