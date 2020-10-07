#ifndef CHANNELDELETECHANNELPERMISSION_H
#define CHANNELDELETECHANNELPERMISSION_H

#include "route.h"


class ChannelDeleteChannelPermission : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/permissions/{overwrite.id}";

    ChannelDeleteChannelPermission(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::OVERWRITE_ID_TOKEN] = context.getOverwriteId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETECHANNELPERMISSION_H
