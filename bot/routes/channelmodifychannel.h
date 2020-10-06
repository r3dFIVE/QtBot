#ifndef CHANNELMODIFYCHANNEL_H
#define CHANNELMODIFYCHANNEL_H

#include "route.h"


class ChannelModifyChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}";

    ChannelModifyChannel(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(PATCH, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELMODIFYCHANNEL_H
