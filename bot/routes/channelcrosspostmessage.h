#ifndef CHANNELCROSSPOSTMESSAGE_H
#define CHANNELCROSSPOSTMESSAGE_H

#include "route.h"


class ChannelCrosspostMessage : public Route
{
public:
    ChannelCrosspostMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}/crosspost";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELCROSSPOSTMESSAGE_H
