#ifndef CHANNELGETREACTIONS_H
#define CHANNELGETREACTIONS_H

#include "route.h"


class ChannelGetReactions : public Route
{
public:
    ChannelGetReactions(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        endpoint.replace(Route::EMOJI_TOKEN, context.getEmoji().toString());

        buildRequest(endpoint, GET, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGETREACTIONS_H
