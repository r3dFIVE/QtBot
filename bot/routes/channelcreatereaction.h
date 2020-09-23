#ifndef CHANNELCREATEREACTION_H
#define CHANNELCREATEREACTION_H

#include "route.h"


class ChannelCreateReaction : public Route
{
public:
    ChannelCreateReaction(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        endpoint.replace(Route::EMOJI_TOKEN, context.getEmoji().toString());

        buildRequest(endpoint, PUT, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELCREATEREACTION_H
