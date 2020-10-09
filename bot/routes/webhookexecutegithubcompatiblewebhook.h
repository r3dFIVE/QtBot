#ifndef WEBHOOKEXECUTEGITHUBCOMPATIBLEWEBHOOK_H
#define WEBHOOKEXECUTEGITHUBCOMPATIBLEWEBHOOK_H

#include "route.h"


class WebhookExecuteGithubCompatibleWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}/github";

    WebhookExecuteGithubCompatibleWebhook(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(POST, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN], context);
    }
};

#endif // WEBHOOKEXECUTEGITHUBCOMPATIBLEWEBHOOK_H
