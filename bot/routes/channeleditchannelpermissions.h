#ifndef CHANNELEDITCHANNELPERMISSIONS_H
#define CHANNELEDITCHANNELPERMISSIONS_H

#include "route.h"


class ChannelEditChannelPermissions : public Route
{
public:
    ChannelEditChannelPermissions(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/permissions/{overwrite.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::OVERWRITE_ID_TOKEN, context.getOverwriteId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELEDITCHANNELPERMISSIONS_H
