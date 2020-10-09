#ifndef WEBHOOKCREATEWEBHOOK_H
#define WEBHOOKCREATEWEBHOOK_H

#include "route.h"


class WebhookCreateWebhook : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/webhooks";

    WebhookCreateWebhook(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // WEBHOOKCREATEWEBHOOK_H
