#ifndef CHANNELCREATEMESSAGE_H
#define CHANNELCREATEMESSAGE_H

#include "route.h"


class ChannelCreateMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages";

    ChannelCreateMessage(const EventContext &context) {
        QString channelId = context.getChannelId().toString();        

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELCREATEMESSAGE_H
