#ifndef CHANNELDELETECHANNEL_H
#define CHANNELDELETECHANNEL_H

#include "route.h"


class ChannelDeleteChannel : public Route
{
public:
    ChannelDeleteChannel(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETECHANNEL_H
