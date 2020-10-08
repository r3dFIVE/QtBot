#ifndef WEBHOOKGETGUILDWEBHOOKS_H
#define WEBHOOKGETGUILDWEBHOOKS_H

#include "route.h"


class WebhookGetGuildWebhooks : public Route
{
public:
    const QString PATH = "/guild/{guild.id}/webhooks";

    WebhookGetGuildWebhooks(const EventContext &context) {
        QString guildId = context.getGuildId().toString();

        _pathParams[Route::GUILD_ID_TOKEN] = guildId;

        buildRequest(GET, PATH, guildId, context.getTargetPayload());
    }
};

#endif // WEBHOOKGETGUILDWEBHOOKS_H
