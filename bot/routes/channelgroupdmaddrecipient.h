#ifndef CHANNELGROUPDMADDRECIPIENT_H
#define CHANNELGROUPDMADDRECIPIENT_H

#include "route.h"


class ChannelGroupDmAddRecipient : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/recipients/{user.id}";

    ChannelGroupDmAddRecipient(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, _pathParams[Route::USER_ID_TOKEN], context);
    }
};

#endif // CHANNELGROUPDMADDRECIPIENT_H
