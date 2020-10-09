#ifndef WEBHOOKGETWEBHOOK_H
#define WEBHOOKGETWEBHOOK_H

#include "route.h"


class WebhookGetWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}";

    WebhookGetWebhook(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        buildRequest(GET, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN]);
    }
};


#endif // WEBHOOKGETWEBHOOK_H
