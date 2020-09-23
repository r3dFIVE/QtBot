#ifndef CHANNELGETPINNEDMESSAGES_H
#define CHANNELGETPINNEDMESSAGES_H

#include "route.h"


class ChannelGetPinnedMessages : public Route
{
public:
    ChannelGetPinnedMessages(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/pins/{message.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, GET, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGETPINNEDMESSAGES_H
