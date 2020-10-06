#ifndef CHANNELDELETEALLREACTIONS_H
#define CHANNELDELETEALLREACTIONS_H

#include "route.h"


class ChannelDeleteAllReactions : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions";

    ChannelDeleteAllReactions(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEALLREACTIONS_H
