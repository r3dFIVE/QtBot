#ifndef CHANNELGETCHANNEL_H
#define CHANNELGETCHANNEL_H

#include "route.h"


class ChannelGetChannel : public Route
{
public:
    ChannelGetChannel(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, GET, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGETCHANNEL_H
