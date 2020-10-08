#ifndef WEBHOOKMODIFYWEBHOOK_H
#define WEBHOOKMODIFYWEBHOOK_H

#include "route.h"


class WebhookModifyWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}";

    WebhookModifyWebhook(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        buildRequest(PATCH, PATH, webhookId, context.getTargetPayload());
    }
};

#endif // WEBHOOKMODIFYWEBHOOK_H
