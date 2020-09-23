#ifndef CHANNELFOLLOWNEWSCHANNEL_H
#define CHANNELFOLLOWNEWSCHANNEL_H

#include "route.h"


class ChannelFollowNewsChannel : public Route
{
public:
    ChannelFollowNewsChannel(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/followers";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELFOLLOWNEWSCHANNEL_H
