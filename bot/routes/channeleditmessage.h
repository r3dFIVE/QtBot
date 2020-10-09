#ifndef CHANNELEDITMESSAGE_H
#define CHANNELEDITMESSAGE_H

#include "route.h"


class ChannelEditMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}";

    ChannelEditMessage(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELEDITMESSAGE_H
