#ifndef CHANNELGETCHANNELMESSAGE_H
#define CHANNELGETCHANNELMESSAGE_H

#include "route.h"


class ChannelGetChannelMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}";

    ChannelGetChannelMessage(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(GET, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELGETCHANNELMESSAGE_H
