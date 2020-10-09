#ifndef WEBHOOKMODIFYWEBHOOKWITHTOKEN_H
#define WEBHOOKMODIFYWEBHOOKWITHTOKEN_H

#include "route.h"


class WebhookModifyWebhookWithToken : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}";

    WebhookModifyWebhookWithToken(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(PATCH, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN], context);
    }
};

#endif // WEBHOOKMODIFYWEBHOOKWITHTOKEN_H
