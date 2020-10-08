#ifndef WEBHOOKGETWEBHOOKWITHTOKEN_H
#define WEBHOOKGETWEBHOOKWITHTOKEN_H

#include "route.h"


class WebhookGetWebhookWithToken : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}";

    WebhookGetWebhookWithToken(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(GET, PATH, webhookId, context.getTargetPayload());
    }
};

#endif // WEBHOOKGETWEBHOOKWITHTOKEN_H
