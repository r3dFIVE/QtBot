#ifndef CHANNELDELETEUSERREACTION_H
#define CHANNELDELETEUSERREACTION_H

#include "route.h"


class ChannelDeleteUserReaction : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}";

    ChannelDeleteUserReaction(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        _pathParams[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEUSERREACTION_H
