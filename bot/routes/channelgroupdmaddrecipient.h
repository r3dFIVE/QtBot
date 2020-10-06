#ifndef CHANNELGROUPDMADDRECIPIENT_H
#define CHANNELGROUPDMADDRECIPIENT_H

#include "route.h"


class ChannelGroupDmAddRecipient : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/recipients/{user.id}";

    ChannelGroupDmAddRecipient(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(PUT, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGROUPDMADDRECIPIENT_H
