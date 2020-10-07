#ifndef CHANNELDELETEPINNEDCHANNELMESSAGE_H
#define CHANNELDELETEPINNEDCHANNELMESSAGE_H

#include "route.h"


class ChannelDeletePinnedChannelMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/pins/{message.id}";

    ChannelDeletePinnedChannelMessage(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEPINNEDCHANNELMESSAGE_H
