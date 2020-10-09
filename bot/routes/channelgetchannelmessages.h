#ifndef CHANNELGETCHANNELMESSAGES_H
#define CHANNELGETCHANNELMESSAGES_H

#include "route.h"


class ChannelGetChannelMessages : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages";

    ChannelGetChannelMessages(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(GET, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELGETCHANNELMESSAGES_H
