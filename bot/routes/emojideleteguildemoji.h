#ifndef EMOJIDELETEGUILDEMOJI_H
#define EMOJIDELETEGUILDEMOJI_H

#include "route.h"


class EmojiDeleteGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis/{emoji.id}";

    EmojiDeleteGuildEmoji(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::GUILD_ID_TOKEN]);
    }
};

#endif // EMOJIDELETEGUILDEMOJI_H
