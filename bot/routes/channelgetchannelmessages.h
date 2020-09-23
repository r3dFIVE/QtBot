#ifndef CHANNELGETCHANNELMESSAGES_H
#define CHANNELGETCHANNELMESSAGES_H

#include "route.h"


class ChannelGetChannelMessages : public Route
{
public:
    ChannelGetChannelMessages(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, GET, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGETCHANNELMESSAGES_H
