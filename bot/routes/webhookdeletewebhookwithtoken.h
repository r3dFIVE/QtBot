#ifndef WEBHOOKDELETEWEBHOOKWITHTOKEN_H
#define WEBHOOKDELETEWEBHOOKWITHTOKEN_H

#include "route.h"


class WebhookDeleteWebhookWithToken : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}";

    WebhookDeleteWebhookWithToken(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(DELETE, PATH, webhookId, context.getTargetPayload());
    }
};

#endif // WEBHOOKDELETEWEBHOOKWITHTOKEN_H
