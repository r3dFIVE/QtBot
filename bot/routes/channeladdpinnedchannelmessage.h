#ifndef CHANNELADDPINNEDCHANNELMESSAGE_H
#define CHANNELADDPINNEDCHANNELMESSAGE_H

#include "route.h"


class ChannelAddPinnedChannelMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/pins/{message.id}";

    ChannelAddPinnedChannelMessage(const EventContext &context) {        
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(PUT, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELADDPINNEDCHANNELMESSAGE_H
