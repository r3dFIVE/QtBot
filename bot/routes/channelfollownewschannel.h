#ifndef CHANNELFOLLOWNEWSCHANNEL_H
#define CHANNELFOLLOWNEWSCHANNEL_H

#include "route.h"


class ChannelFollowNewsChannel : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/followers";

    ChannelFollowNewsChannel(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELFOLLOWNEWSCHANNEL_H
