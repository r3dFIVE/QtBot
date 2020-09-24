#ifndef CHANNELEDITMESSAGE_H
#define CHANNELEDITMESSAGE_H

#include "route.h"


class ChannelEditMessage : public Route
{
public:
    ChannelEditMessage(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, PATCH, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELEDITMESSAGE_H