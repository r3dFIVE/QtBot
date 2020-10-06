#ifndef CHANNELFOLLOWNEWSCHANNEL_H
#define CHANNELFOLLOWNEWSCHANNEL_H

#include "route.h"


class ChannelFollowNewsChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/followers";

    ChannelFollowNewsChannel(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELFOLLOWNEWSCHANNEL_H
