#ifndef WEBHOOKDELETEWEBHOOK_H
#define WEBHOOKDELETEWEBHOOK_H

#include "route.h"


class WebhookDeleteWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}";

    WebhookDeleteWebhook(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        buildRequest(DELETE, PATH, webhookId, context.getTargetPayload());
    }
};

#endif // WEBHOOKDELETEWEBHOOK_H
