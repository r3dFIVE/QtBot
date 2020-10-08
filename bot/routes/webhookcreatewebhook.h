#ifndef WEBHOOKCREATEWEBHOOK_H
#define WEBHOOKCREATEWEBHOOK_H

#include "route.h"


class WebhookCreateWebhook : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/webhooks";

    WebhookCreateWebhook(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // WEBHOOKCREATEWEBHOOK_H
