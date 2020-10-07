#ifndef CHANNELEDITCHANNELPERMISSIONS_H
#define CHANNELEDITCHANNELPERMISSIONS_H

#include "route.h"


class ChannelEditChannelPermissions : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/permissions/{overwrite.id}";

    ChannelEditChannelPermissions(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::OVERWRITE_ID_TOKEN] = context.getOverwriteId().toString();

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELEDITCHANNELPERMISSIONS_H
