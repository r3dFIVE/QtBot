#ifndef CHANNELGROUPDMADDRECIPIENT_H
#define CHANNELGROUPDMADDRECIPIENT_H

#include "route.h"


class ChannelGroupDmAddRecipient : public Route
{
public:
    ChannelGroupDmAddRecipient(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/recipients/{user.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, PUT, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGROUPDMADDRECIPIENT_H
