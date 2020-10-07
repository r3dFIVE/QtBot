#ifndef CHANNELDELETECHANNEL_H
#define CHANNELDELETECHANNEL_H

#include "route.h"


class ChannelDeleteChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}";

    ChannelDeleteChannel(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETECHANNEL_H
