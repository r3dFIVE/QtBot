#ifndef CHANNELDELETECHANNELPERMISSION_H
#define CHANNELDELETECHANNELPERMISSION_H

#include "route.h"


class ChannelDeleteChannelPermission : public Route
{
public:
    ChannelDeleteChannelPermission(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/permissions/{overwrite.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::OVERWRITE_ID_TOKEN, context.getOverwriteId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETECHANNELPERMISSION_H
