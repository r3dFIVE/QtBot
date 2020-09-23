#ifndef CHANNELDELETEMESSAGE_H
#define CHANNELDELETEMESSAGE_H

#include "route.h"


class ChannelDeleteMessage : public Route
{
public:
    ChannelDeleteMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETEMESSAGE_H
