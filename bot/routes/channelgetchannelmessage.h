#ifndef CHANNELGETCHANNELMESSAGE_H
#define CHANNELGETCHANNELMESSAGE_H

#include "route.h"


class ChannelGetChannelMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}";

    ChannelGetChannelMessage(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(GET, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGETCHANNELMESSAGE_H
