#ifndef WEBHOOKEXECUTEGITHUBCOMPATIBLEWEBHOOK_H
#define WEBHOOKEXECUTEGITHUBCOMPATIBLEWEBHOOK_H

#include "route.h"


class WebhookExecuteGithubCompatibleWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}/github";

    WebhookExecuteGithubCompatibleWebhook(const EventContext &context) {
        QString webhookId = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_ID_TOKEN] = webhookId;

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(POST, PATH, webhookId, context.getTargetPayload());
    }
};

#endif // WEBHOOKEXECUTEGITHUBCOMPATIBLEWEBHOOK_H
