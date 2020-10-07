#ifndef EMOJIDELETEGUILDEMOJI_H
#define EMOJIDELETEGUILDEMOJI_H

#include "route.h"


class EmojiDeleteGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis/{emoji.id}";

    EmojiDeleteGuildEmoji(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(DELETE, PATH, guildId, context.getTargetPayload());
    }
};

#endif // EMOJIDELETEGUILDEMOJI_H
