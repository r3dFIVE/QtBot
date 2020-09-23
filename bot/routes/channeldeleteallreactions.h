#ifndef CHANNELDELETEALLREACTIONS_H
#define CHANNELDELETEALLREACTIONS_H

#include "route.h"


class ChannelDeleteAllReactions : public Route
{
public:
    ChannelDeleteAllReactions(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}/reactions";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETEALLREACTIONS_H
