#ifndef CHANNELBULKMESSAGESDELETE_H
#define CHANNELBULKMESSAGESDELETE_H

#include "route.h"


class ChannelBulkDeleteMessages : public Route
{
public:
    ChannelBulkDeleteMessages(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/bulk-delete";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        buildRequest(endpoint, POST, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELBULKMESSAGESDELETE_H
