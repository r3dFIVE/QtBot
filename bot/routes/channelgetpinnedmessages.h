#ifndef CHANNELGETPINNEDMESSAGES_H
#define CHANNELGETPINNEDMESSAGES_H

#include "route.h"


class ChannelGetPinnedMessages : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/pins/{message.id}";

    ChannelGetPinnedMessages(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(GET, PATH , channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGETPINNEDMESSAGES_H
