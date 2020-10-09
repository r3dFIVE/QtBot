#ifndef WEBHOOKMODIFYWEBHOOK_H
#define WEBHOOKMODIFYWEBHOOK_H

#include "route.h"


class WebhookModifyWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}";

    WebhookModifyWebhook(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN], context);
    }
};

#endif // WEBHOOKMODIFYWEBHOOK_H
