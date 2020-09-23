#ifndef CHANNELDELETEUSERREACTION_H
#define CHANNELDELETEUSERREACTION_H

#include "route.h"


class ChannelDeleteUserReaction : public Route
{
public:
    ChannelDeleteUserReaction(const EventContext &context) {
        QString endpoint = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}";

        endpoint.replace(Route::CHANNEL_ID_TOKEN, context.getChannelId().toString());

        endpoint.replace(Route::MESSAGE_ID_TOKEN, context.getMessageId().toString());

        endpoint.replace(Route::EMOJI_TOKEN, context.getEmoji().toString());

        endpoint.replace(Route::USER_ID_TOKEN, context.getUserId().toString());

        buildRequest(endpoint, DELETE, CHANNEL_ID_BUCKET, context);
    }
};

#endif // CHANNELDELETEUSERREACTION_H
