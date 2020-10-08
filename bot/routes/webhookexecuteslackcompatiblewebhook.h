#ifndef WEBHOOKEXECUTESLACKCOMPATIBLEWEBHOOK_H
#define WEBHOOKEXECUTESLACKCOMPATIBLEWEBHOOK_H

#include "route.h"


class WebhookExecuteSlackCompatibleWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}/slack";

    WebhookExecuteSlackCompatibleWebhook(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(POST, PATH, webhookId, context.getTargetPayload());
    }
};

#endif // WEBHOOKEXECUTESLACKCOMPATIBLEWEBHOOK_H
