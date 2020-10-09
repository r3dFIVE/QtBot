#ifndef WEBHOOKEXECUTESLACKCOMPATIBLEWEBHOOK_H
#define WEBHOOKEXECUTESLACKCOMPATIBLEWEBHOOK_H

#include "route.h"


class WebhookExecuteSlackCompatibleWebhook : public Route
{
public:
    const QString PATH = "/webhooks/{webhook.id}/{webhook.token}/slack";

    WebhookExecuteSlackCompatibleWebhook(const EventContext &context) {
        _pathParams[Route::WEBHOOK_ID_TOKEN] = context.getWebhookId().toString();

        _pathParams[Route::WEBHOOK_TOKEN_TOKEN] = context.getWebhookToken().toString();

        buildRequest(POST, PATH, _pathParams[Route::WEBHOOK_ID_TOKEN], context);
    }
};

#endif // WEBHOOKEXECUTESLACKCOMPATIBLEWEBHOOK_H
