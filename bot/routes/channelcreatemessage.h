#ifndef CHANNELCREATEMESSAGE_H
#define CHANNELCREATEMESSAGE_H

#include "route.h"


class ChannelCreateMessage : public Route
{
public:
    ChannelCreateMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELCREATEMESSAGE_H
