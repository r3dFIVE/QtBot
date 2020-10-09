#ifndef CHANNELGETCHANNELINVITES_H
#define CHANNELGETCHANNELINVITES_H

#include "route.h"


class ChannelGetChannelInvites : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/invites";

    ChannelGetChannelInvites(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(GET, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELGETCHANNELINVITES_H
