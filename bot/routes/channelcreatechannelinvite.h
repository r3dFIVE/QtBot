#ifndef CHANNELCREATECHANNELINVITE_H
#define CHANNELCREATECHANNELINVITE_H

#include "route.h"


class ChannelCreateChannelInvite : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/invites";

    ChannelCreateChannelInvite(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELCREATECHANNELINVITE_H
