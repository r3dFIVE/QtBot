#ifndef CHANNELTRIGGERTYPINGINDICATOR_H
#define CHANNELTRIGGERTYPINGINDICATOR_H

#include "route.h"


class ChannelTriggerTypingIndicator : public Route
{
public:
    ChannelTriggerTypingIndicator(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/typing";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELTRIGGERTYPINGINDICATOR_H
