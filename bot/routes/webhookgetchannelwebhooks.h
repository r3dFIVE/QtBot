#ifndef WEBHOOKGETCHANNELWEBHOOKS_H
#define WEBHOOKGETCHANNELWEBHOOKS_H

#include "route.h"


class WebhookGetChannelWebhooks : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/webhooks";

    WebhookGetChannelWebhooks(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(GET, PATH, channelId, context.getTargetPayload());
    }
};

#endif // WEBHOOKGETCHANNELWEBHOOKS_H
