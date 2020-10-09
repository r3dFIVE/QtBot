#ifndef CHANNELBULKMESSAGESDELETE_H
#define CHANNELBULKMESSAGESDELETE_H

#include "route.h"


class ChannelBulkDeleteMessages : public Route
{
public:    
    const QString PATH = "/channels/{channel.id}/messages/bulk-delete";

    ChannelBulkDeleteMessages(const EventContext &context) {
        _pathParams[Route::CHANNEL_ID_TOKEN] = context.getChannelId().toString();

        buildRequest(POST, PATH, _pathParams[Route::CHANNEL_ID_TOKEN], context);
    }
};

#endif // CHANNELBULKMESSAGESDELETE_H
