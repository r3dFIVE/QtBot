#ifndef EMOJICREATEGUILDEMOJI_H
#define EMOJICREATEGUILDEMOJI_H

#include "route.h"


class EmojiCreateGuildEmoji : public Route
{
public:
    const QString PATH = "/guilds/{guild.id}/emojis";

    EmojiCreateGuildEmoji(const EventContext &context) {
        _pathParams[Route::GUILD_ID_TOKEN] = context.getGuildId().toString();

        buildRequest(POST, PATH, _pathParams[Route::GUILD_ID_TOKEN], context);
    }
};

#endif // EMOJICREATEGUILDEMOJI_H
