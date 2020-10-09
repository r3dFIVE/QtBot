#ifndef CHANNELTRIGGERTYPINGINDICATOR_H
#define CHANNELTRIGGERTYPINGINDICATOR_H

#include "route.h"


class ChannelTriggerTypingIndicator : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/typing";

    ChannelTriggerTypingIndicator(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELTRIGGERTYPINGINDICATOR_H
