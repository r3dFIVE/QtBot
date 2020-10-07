#ifndef CHANNELGETCHANNEL_H
#define CHANNELGETCHANNEL_H

#include "route.h"


class ChannelGetChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}";

    ChannelGetChannel(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(GET, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGETCHANNEL_H
