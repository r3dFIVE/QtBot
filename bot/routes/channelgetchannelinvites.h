#ifndef CHANNELGETCHANNELINVITES_H
#define CHANNELGETCHANNELINVITES_H

#include "route.h"


class ChannelGetChannelInvites : public Route
{
public:
    ChannelGetChannelInvites(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/invites";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, GET, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGETCHANNELINVITES_H
