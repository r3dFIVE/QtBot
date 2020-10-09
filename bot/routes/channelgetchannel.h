#ifndef CHANNELGETCHANNEL_H
#define CHANNELGETCHANNEL_H

#include "route.h"


class ChannelGetChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}";

    ChannelGetChannel(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(GET, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELGETCHANNEL_H
