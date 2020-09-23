#ifndef CHANNELDELETEALLREACTIONSFOREMOJI_H
#define CHANNELDELETEALLREACTIONSFOREMOJI_H

#include "route.h"


class ChannelDeleteAllReactionsForEmoji : public Route
{
public:
    ChannelDeleteAllReactionsForEmoji(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        endpoint.replace(Route::EMOJI_TOKEN, context.getEmoji().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETEALLREACTIONSFOREMOJI_H
