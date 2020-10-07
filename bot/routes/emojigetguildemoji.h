#ifndef EMOJIGETGUILDEMOJI_H
#define EMOJIGETGUILDEMOJI_H

#include "route.h"


class EmojiGetGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis/{emoji.id}";

    EmojiGetGuildEmoji(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // EMOJIGETGUILDEMOJI_H
