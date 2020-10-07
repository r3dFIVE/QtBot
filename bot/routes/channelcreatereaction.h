#ifndef CHANNELCREATEREACTION_H
#define CHANNELCREATEREACTION_H

#include "route.h"


class ChannelCreateReaction : public Route
{
public:
    const QString PATH = "/channels/{channel.id}/messages/{message.id}/reactions/{emoji}/@me";

    ChannelCreateReaction(const EventContext &context) {
        QString channelId = context.getChannelId().toString();

        _pathParams[Route::CHANNEL_ID_TOKEN] = channelId;

        _pathParams[Route::MESSAGE_ID_TOKEN] = context.getMessageId().toString();

        _pathParams[Route::EMOJI_TOKEN] = context.getEmoji().toString();

        buildRequest(POST, PATH, channelId, context.getTargetPayload());
    }
};

#endif // CHANNELCREATEREACTION_H
