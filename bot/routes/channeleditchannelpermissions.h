#ifndef CHANNELEDITCHANNELPERMISSIONS_H
#define CHANNELEDITCHANNELPERMISSIONS_H

#include "route.h"


class ChannelEditChannelPermissions : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/permissions/{overwrite.id}";

    ChannelEditChannelPermissions(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::OVERWRITE_ID_TOKEN] = context.getOverwriteId().toString();

        buildRequest(PUT, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELEDITCHANNELPERMISSIONS_H
