#ifndef WEBHOOKGETWEBHOOK_H
#define WEBHOOKGETWEBHOOK_H

#include "route.h"


class WebhookGetWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}";

    WebhookGetWebhook(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        buildRequest(GET, PATH, webhookId, context.getTargetPayload());
    }
};


#endif // WEBHOOKGETWEBHOOK_H
