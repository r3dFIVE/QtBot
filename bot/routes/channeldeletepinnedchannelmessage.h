#ifndef CHANNELDELETEPINNEDCHANNELMESSAGE_H
#define CHANNELDELETEPINNEDCHANNELMESSAGE_H

#include "route.h"


class ChannelDeletePinnedChannelMessage : public Route
{
public:
    ChannelDeletePinnedChannelMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/pins/{message.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETEPINNEDCHANNELMESSAGE_H
