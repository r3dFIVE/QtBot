#ifndef CHANNELTRIGGERTYPINGINDICATOR_H
#define CHANNELTRIGGERTYPINGINDICATOR_H

#include "route.h"


class ChannelTriggerTypingIndicator : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/typing";

    ChannelTriggerTypingIndicator(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELTRIGGERTYPINGINDICATOR_H
