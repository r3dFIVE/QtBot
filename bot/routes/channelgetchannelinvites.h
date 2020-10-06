#ifndef CHANNELGETCHANNELINVITES_H
#define CHANNELGETCHANNELINVITES_H

#include "route.h"


class ChannelGetChannelInvites : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/invites";

    ChannelGetChannelInvites(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(GET, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGETCHANNELINVITES_H
