#ifndef CHANNELDELETEMESSAGE_H
#define CHANNELDELETEMESSAGE_H

#include "route.h"


class ChannelDeleteMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}";

    ChannelDeleteMessage(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEMESSAGE_H
