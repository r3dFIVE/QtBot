#ifndef CHANNELDELETEALLREACTIONS_H
#define CHANNELDELETEALLREACTIONS_H

#include "route.h"


class ChannelDeleteAllReactions : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions";

    ChannelDeleteAllReactions(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELDELETEALLREACTIONS_H
