#ifndef CHANNELGROUPDMREMOVERECIPIENT_H
#define CHANNELGROUPDMREMOVERECIPIENT_H

#include "route.h"


class ChannelGroupDmRemoveRecipient : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/recipients/{user.id}";

    ChannelGroupDmRemoveRecipient(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, _pathParams[Route::CHANNEL_ID_TOKEN]);
    }
};

#endif // CHANNELGROUPDMREMOVERECIPIENT_H
