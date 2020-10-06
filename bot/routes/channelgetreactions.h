#ifndef CHANNELGETREACTIONS_H
#define CHANNELGETREACTIONS_H

#include "route.h"


class ChannelGetReactions : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}";

    ChannelGetReactions(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        _params[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(GET, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGETREACTIONS_H
