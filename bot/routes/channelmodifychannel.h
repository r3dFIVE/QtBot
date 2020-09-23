#ifndef CHANNELMODIFYCHANNEL_H
#define CHANNELMODIFYCHANNEL_H

#include "route.h"


class ChannelModifyChannel : public Route
{
public:
    ChannelModifyChannel(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, PATCH, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELMODIFYCHANNEL_H
