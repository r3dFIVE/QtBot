#ifndef CHANNELDELETEUSERREACTION_H
#define CHANNELDELETEUSERREACTION_H

#include "route.h"


class ChannelDeleteUserReaction : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/{user.id}";

    ChannelDeleteUserReaction(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        _params[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        _params[Route::USER_ID_TOKEN] = context.getUserId().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEUSERREACTION_H
