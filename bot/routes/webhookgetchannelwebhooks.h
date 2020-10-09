#ifndef WEBHOOKGETCHANNELWEBHOOKS_H
#define WEBHOOKGETCHANNELWEBHOOKS_H

#include "route.h"


class WebhookGetChannelWebhooks : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/webhooks";

    WebhookGetChannelWebhooks(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(GET, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // WEBHOOKGETCHANNELWEBHOOKS_H
