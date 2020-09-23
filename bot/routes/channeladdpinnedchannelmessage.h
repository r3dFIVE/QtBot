#ifndef CHANNELADDPINNEDCHANNELMESSAGE_H
#define CHANNELADDPINNEDCHANNELMESSAGE_H

#include "route.h"


class ChannelAddPinnedChannelMessage : public Route
{
public:
    ChannelAddPinnedChannelMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/pins/{message.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, PUT, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELADDPINNEDCHANNELMESSAGE_H
