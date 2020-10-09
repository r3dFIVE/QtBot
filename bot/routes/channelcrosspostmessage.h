#ifndef CHANNELCROSSPOSTMESSAGE_H
#define CHANNELCROSSPOSTMESSAGE_H

#include "route.h"


class ChannelCrosspostMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/crosspost";

    ChannelCrosspostMessage(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELCROSSPOSTMESSAGE_H
