#ifndef CHANNELGETCHANNELMESSAGE_H
#define CHANNELGETCHANNELMESSAGE_H

#include "route.h"


class ChannelGetChannelMessage : public Route
{
public:
    ChannelGetChannelMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, GET, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGETCHANNELMESSAGE_H
