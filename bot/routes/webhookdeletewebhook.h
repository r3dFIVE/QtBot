#ifndef WEBHOOKDELETEWEBHOOK_H
#define WEBHOOKDELETEWEBHOOK_H

#include "route.h"


class WebhookDeleteWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}";

    WebhookDeleteWebhook(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN]);
    }
};

#endif // WEBHOOKDELETEWEBHOOK_H
