#ifndef CHANNELDELETEALLREACTIONSFOREMOJI_H
#define CHANNELDELETEALLREACTIONSFOREMOJI_H

#include "route.h"


class ChannelDeleteAllReactionsForEmoji : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}";

    ChannelDeleteAllReactionsForEmoji(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEALLREACTIONSFOREMOJI_H
