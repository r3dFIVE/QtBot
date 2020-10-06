#ifndef CHANNELBULKMESSAGESDELETE_H
#define CHANNELBULKMESSAGESDELETE_H

#include "route.h"


class ChannelBulkDeleteMessages : public Route
{
public:    
    const QString PATH = "/channels/{channel.id}/messages/bulk-delete";

    ChannelBulkDeleteMessages(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELBULKMESSAGESDELETE_H
