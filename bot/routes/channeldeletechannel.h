#ifndef CHANNELDELETECHANNEL_H
#define CHANNELDELETECHANNEL_H

#include "route.h"


class ChannelDeleteChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}";

    ChannelDeleteChannel(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELDELETECHANNEL_H
