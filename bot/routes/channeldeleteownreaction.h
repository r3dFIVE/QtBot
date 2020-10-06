#ifndef CHANNELDELETEOWNREACTION_H
#define CHANNELDELETEOWNREACTION_H

#include "route.h"


class ChannelDeleteOwnReaction : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me";

    ChannelDeleteOwnReaction(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _params[Route::CHANNEL_ID_TOKEN] = channelId;

        _params[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        _params[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(DELETE, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELDELETEOWNREACTION_H
