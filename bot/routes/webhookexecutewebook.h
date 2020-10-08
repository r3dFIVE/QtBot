#ifndef WEBHOOKEXECUTEWEBOOK_H
#define WEBHOOKEXECUTEWEBOOK_H

#include "route.h"


class WebhookExecuteWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}";

    WebhookExecuteWebhook(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(POST, PATH, webhookId, context.getTargetPayload(), context.getQueryParams());
    }
};

#endif // WEBHOOKEXECUTEWEBOOK_H
