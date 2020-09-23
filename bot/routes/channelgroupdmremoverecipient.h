#ifndef CHANNELGROUPDMREMOVERECIPIENT_H
#define CHANNELGROUPDMREMOVERECIPIENT_H

#include "route.h"


class ChannelGroupDmRemoveRecipient : public Route
{
public:
    ChannelGroupDmRemoveRecipient(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/recipients/{user.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELGROUPDMREMOVERECIPIENT_H
