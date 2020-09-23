#ifndef CHANNELCREATECHANNELINVITE_H
#define CHANNELCREATECHANNELINVITE_H

#include "route.h"


class ChannelCreateChannelInvite : public Route
{
public:
    ChannelCreateChannelInvite(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/invites";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELCREATECHANNELINVITE_H
