#ifndef CHANNELADDPINNEDCHANNELMESSAGE_H
#define CHANNELADDPINNEDCHANNELMESSAGE_H

#include "route.h"


class ChannelAddPinnedChannelMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/pins/{message.id}";

    ChannelAddPinnedChannelMessage(const EventContext &context) {        
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(PUT, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELADDPINNEDCHANNELMESSAGE_H
