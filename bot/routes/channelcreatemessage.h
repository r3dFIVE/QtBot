#ifndef CHANNELCREATEMESSAGE_H
#define CHANNELCREATEMESSAGE_H

#include "route.h"


class ChannelCreateMessage : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages";

    ChannelCreateMessage(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();;

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELCREATEMESSAGE_H
