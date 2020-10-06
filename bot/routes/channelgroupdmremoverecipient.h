#ifndef CHANNELGROUPDMREMOVERECIPIENT_H
#define CHANNELGROUPDMREMOVERECIPIENT_H

#include "route.h"


class ChannelGroupDmRemoveRecipient : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/recipients/{user.id}";

    ChannelGroupDmRemoveRecipient(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELGROUPDMREMOVERECIPIENT_H
