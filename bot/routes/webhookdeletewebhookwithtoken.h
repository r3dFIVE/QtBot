#ifndef WEBHOOKDELETEWEBHOOKWITHTOKEN_H
#define WEBHOOKDELETEWEBHOOKWITHTOKEN_H

#include "route.h"


class WebhookDeleteWebhookWithToken : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}";

    WebhookDeleteWebhookWithToken(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN]);
    }
};

#endif // WEBHOOKDELETEWEBHOOKWITHTOKEN_H
