#ifndef CHANNELGETCHANNELMESSAGES_H
#define CHANNELGETCHANNELMESSAGES_H

#include "route.h"


class ChannelGetChannelMessages : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages";

    ChannelGetChannelMessages(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(GET, PATH, channelId, context.getTargetPayload(), context.getQueryParams());
    }
};

#endif // CHANNELGETCHANNELMESSAGES_H
