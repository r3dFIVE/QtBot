#ifndef EMOJIMODIFYGUILDEMOJI_H
#define EMOJIMODIFYGUILDEMOJI_H

#include "route.h"


class EmojiModifyGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis/{emoji.id}";

    EmojiModifyGuildEmoji(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(PATCH, PATH, guildId, context.getTargetPayload());
    }
};

#endif // EMOJIMODIFYGUILDEMOJI_H
