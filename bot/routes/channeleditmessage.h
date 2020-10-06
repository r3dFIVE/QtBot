#ifndef CHANNELEDITMESSAGE_H
#define CHANNELEDITMESSAGE_H

#include "route.h"


class ChannelEditMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}";

    ChannelEditMessage(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(PATCH, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELEDITMESSAGE_H
