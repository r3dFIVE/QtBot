#ifndef CHANNELGETPINNEDMESSAGES_H
#define CHANNELGETPINNEDMESSAGES_H

#include "route.h"


class ChannelGetPinnedMessages : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/pins/{message.id}";

    ChannelGetPinnedMessages(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(GET, PATH , _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELGETPINNEDMESSAGES_H
