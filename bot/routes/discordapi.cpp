#include "discordapi.h"

#include "channeleditmessage.h"
#include "channelcreatemessage.h"
#include "channelcreatereaction.h"
#include "channelcrosspostmessage.h"
#include "channeldeleteallreactions.h"
#include "channeldeleteallreactionsforemoji.h"
#include "channeldeletechannel.h"
#include "channeldeleteownreaction.h"
#include "channeldeleteuserreaction.h"
#include "channelgetchannel.h"
#include "channelgetchannelmessage.h"
#include "channelgetchannelmessages.h"
#include "channelgetreactions.h"
#include "channelmodifychannel.h"
#include "channeldeletemessage.h"
#include "channelbulkmessagesdelete.h"
#include "channeleditchannelpermissions.h"
#include "channelgetchannelinvites.h"
#include "channelcreatechannelinvite.h"
#include "channeldeletechannelpermission.h"
#include "channelfollownewschannel.h"
#include "channeltriggertypingindicator.h"
#include "channelgetpinnedmessages.h"
#include "channeladdpinnedchannelmessage.h"
#include "channeldeletepinnedchannelmessage.h"


QString DiscordAPI::_botToken = QString();

EventContext
DiscordAPI::buildRequestContext(const QVariant &contextVariant) {
    EventContext context;

    SerializationUtils::fromVariant(context, contextVariant);

    return context;
}

QVariant
DiscordAPI::buildResponseVariant(QSharedPointer<EventContext> apiResponse) {
    QVariant responseContext;

    if (apiResponse) {
        responseContext = SerializationUtils::toVariant(*apiResponse);
    }

    return responseContext;
}

void
DiscordAPI::setBotToken(const QString &botToken) {
    _botToken = botToken;
}

QVariant
DiscordAPI::channelGetChannel(const QVariant &context) {
    ChannelGetChannel getChannel(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getChannel));
}

QVariant
DiscordAPI::channelModifyChannel(const QVariant &context) {
    ChannelModifyChannel modifyChannel(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyChannel));
}

QVariant
DiscordAPI::channelDeleteChannel(const QVariant &context) {
    ChannelDeleteChannel deleteChannel(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteChannel));
}

QVariant
DiscordAPI::channelGetChannelMessages(const QVariant &context) {
    ChannelGetChannelMessages getChannelMessages(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getChannelMessages));
}

QVariant
DiscordAPI::channelGetChannelMessage(const QVariant &context) {
    ChannelGetChannelMessage getChannelMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getChannelMessage));
}

QVariant
DiscordAPI::channelCreateMessage(const QVariant &context) {
    ChannelCreateMessage createMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createMessage));
}

QVariant
DiscordAPI::channelCrosspostMessage(const QVariant &context) {
    ChannelCrosspostMessage crosspostMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(crosspostMessage));
}

QVariant
DiscordAPI::channelCreateReaction(const QVariant &context) {
    ChannelCreateReaction createReaction(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createReaction));
}

QVariant
DiscordAPI::channelDeleteOwnReaction(const QVariant &context) {
    ChannelDeleteOwnReaction deleteOwnReaction(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteOwnReaction));
}

QVariant
DiscordAPI::channelDeleteUserReaction(const QVariant &context) {
    ChannelDeleteUserReaction deleteUserReaction(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteUserReaction));
}

QVariant
DiscordAPI::channelGetReactions(const QVariant &context) {
    ChannelGetReactions getReactions(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getReactions));
}

QVariant
DiscordAPI::channelDeleteAllReactions(const QVariant &context) {
    ChannelDeleteAllReactions deleteAllReactions(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteAllReactions));
}

QVariant
DiscordAPI::channelDeleteAllReactionsForEmoji(const QVariant &context) {
    ChannelDeleteAllReactionsForEmoji deleteAllReactionsForEmoji(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteAllReactionsForEmoji));
}

QVariant
DiscordAPI::channelEditMessage(const QVariant &context) {
    ChannelEditMessage editMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(editMessage));
}

QVariant
DiscordAPI::channelDeleteMessage(const QVariant &context) {
    ChannelDeleteMessage deleteMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteMessage));
}

QVariant
DiscordAPI::channelBulkDeleteMessages(const QVariant &context) {
    ChannelBulkDeleteMessages bulkDeleteMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(bulkDeleteMessage));
}

QVariant
DiscordAPI::channelEditChannelPermissions(const QVariant &context) {
    ChannelEditChannelPermissions editChannelPermissions(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(editChannelPermissions));
}

QVariant
DiscordAPI::channelGetChannelInvites(const QVariant &context) {
    ChannelGetChannelInvites getChannelInvites(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getChannelInvites));
}

QVariant
DiscordAPI::channelCreateChannelInvite(const QVariant &context) {
    ChannelCreateChannelInvite createChannelInvite(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createChannelInvite));
}

QVariant
DiscordAPI::channelDeleteChannelPermission(const QVariant &context) {
    ChannelDeleteChannelPermission deleteChannelPermission(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteChannelPermission));
}

QVariant
DiscordAPI::channelFollowNewsChannel(const QVariant &context) {
    ChannelFollowNewsChannel followNewsChannel(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(followNewsChannel));
}

QVariant
DiscordAPI::channelTriggerTypingIndicator(const QVariant &context) {
    ChannelTriggerTypingIndicator triggerTypingIndicator(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(triggerTypingIndicator));
}

QVariant
DiscordAPI::channelGetPinnedMessages(const QVariant &context) {
    ChannelGetPinnedMessages getPinnedMessages(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getPinnedMessages));
}

QVariant
DiscordAPI::channelAddPinnedChannelMessage(const QVariant &context) {
    ChannelAddPinnedChannelMessage addPinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(addPinnedChannelMessage));
}

QVariant
DiscordAPI::channelDeletePinnedChannelMessage(const QVariant &context) {
    ChannelDeletePinnedChannelMessage deletePinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deletePinnedChannelMessage));
}

QVariant
DiscordAPI::channelGroupDmAddRecipient(const QVariant &context) {
    ChannelDeletePinnedChannelMessage deletePinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deletePinnedChannelMessage));
}

QVariant
DiscordAPI::channelGroupDmRemoveRecipient(const QVariant &context) {
    ChannelDeletePinnedChannelMessage deletePinnedChannelMessage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deletePinnedChannelMessage));
}
