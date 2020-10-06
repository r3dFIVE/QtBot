#ifndef CHANNELCREATECHANNELINVITE_H
#define CHANNELCREATECHANNELINVITE_H

#include "route.h"


class ChannelCreateChannelInvite : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/invites";

    ChannelCreateChannelInvite(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELCREATECHANNELINVITE_H
