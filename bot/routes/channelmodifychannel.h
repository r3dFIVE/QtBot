#ifndef CHANNELMODIFYCHANNEL_H
#define CHANNELMODIFYCHANNEL_H

#include "route.h"


class ChannelModifyChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}";

    ChannelModifyChannel(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context.getTargetPayload());
    }
};

#endif // CHANNELMODIFYCHANNEL_H
