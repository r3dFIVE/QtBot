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
#include "guildcreateguild.h"
#include "guildgetguild.h"
#include "guildmodifyguild.h"
#include "guilddeleteguild.h"
#include "guildgetguildchannels.h"
#include "guildcreateguildchannel.h"
#include "guildmodifyguildchannelposition.h"
#include "guildgetguildmember.h"
#include "guildlistguildmembers.h"
#include "guildaddguildmember.h"
#include "guildmodifyguildmember.h"
#include "guildmodifycurrentusernick.h"
#include "guildaddguildmemberrole.h"
#include "guildremoveguildmemberrole.h"
#include "guildremoveguildmember.h"
#include "guildgetguildbans.h"
#include "guildgetguildban.h"
#include "guildcreateguildban.h"
#include "guildremoveguildban.h"
#include "guildgetguildroles.h"
#include "guildcreateguildrole.h"
#include "guildmodifyguildroleposition.h"
#include "guildmodifyguildrole.h"
#include "guilddeleteguildrole.h"
#include "guildgetguildprunecount.h"
#include "guildbeginguildprune.h"
#include "guildgetguildvoiceregions.h"
#include "guildgetguildinvites.h"
#include "guildgetguildintegrations.h"
#include "guildcreateguildintegration.h"
#include "guildmodifyguildintegration.h"
#include "guilddeleteguildintegration.h"
#include "guildsyncguildintegration.h"
#include "guildgetguildwidget.h"
#include "guildgetguildembed.h"
#include "guildmodifyguildwidget.h"
#include "guildmodifyguildembed.h"
#include "guildgetvanityurl.h"
#include "guildgetwidgetimage.h"
#include "emojilistguildemojis.h"
#include "emojicreateguildemoji.h"
#include "emojideleteguildemoji.h"
#include "emojigetguildemoji.h"
#include "emojimodifyguildemoji.h"
#include "usergetcurrentuser.h"
#include "usergetuser.h"
#include "usermodifycurrentuser.h"
#include "usergetcurrentuserguilds.h"
#include "usergetuserdms.h"
#include "userleaveguild.h"
#include "usercreatedm.h"
#include "usergetuserconnections.h"


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

QString
DiscordAPI::getBotToken() {
    return _botToken;
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

QVariant
DiscordAPI::guildCreateGuild(const QVariant &context) {
    GuildCreateGuild createGuild(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createGuild));
}

QVariant
DiscordAPI::guildGetGuild(const QVariant &context) {
    GuildGetGuild getGuild(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuild));
}

QVariant
DiscordAPI::guildGetGuildPreview(const QVariant &context) {
    GuildGetGuild getGuild(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuild));
}

QVariant
DiscordAPI::guildModifyGuild(const QVariant &context) {
    GuildModifyGuild modifyGuild(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuild));
}

QVariant
DiscordAPI::guildDeleteGuild(const QVariant &context) {
    GuildDeleteGuild deleteGuild(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteGuild));
}

QVariant
DiscordAPI::guildGetGuildChannels(const QVariant &context) {
    GuildGetGuildChannels getGuildChannels(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildChannels));
}

QVariant
DiscordAPI::guildCreateGuildChannel(const QVariant &context) {
    GuildCreateGuildChannel createGuildChannel(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createGuildChannel));
}

QVariant
DiscordAPI::guildModifyGuildChannelPosition(const QVariant &context) {
    GuildModifyGuildChannelPosition modifyGuildChannelPosition(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildChannelPosition));
}

QVariant
DiscordAPI::guildGetGuildMember(const QVariant &context) {
    GuildGetGuildMember getGuildMember(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildMember));
}

QVariant
DiscordAPI::guildListGuildMembers(const QVariant &context) {
    GuildListGuildMembers listGuildMembers(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(listGuildMembers));
}

QVariant
DiscordAPI::guildAddGuildMember(const QVariant &context) {
    GuildAddGuildMember addGuildMember(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(addGuildMember));
}

QVariant
DiscordAPI::guildModifyGuildMember(const QVariant &context) {
    GuildModifyGuildMember modifyGuildMember(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildMember));
}

QVariant
DiscordAPI::guildModifyCurrentUserNick(const QVariant &context) {
    GuildModifyCurrentUserNick modifyCurrentUserNick(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyCurrentUserNick));
}

QVariant
DiscordAPI::guildAddGuildMemberRole(const QVariant &context) {
    GuildAddGuildMemberRole addGuildMemberRole(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(addGuildMemberRole));
}

QVariant
DiscordAPI::guildRemoveGuildMemberRole(const QVariant &context) {
    GuildRemoveGuildMemberRole removeGuildMemberRole(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(removeGuildMemberRole));
}

QVariant
DiscordAPI::guildRemoveGuildMember(const QVariant &context) {
    GuildRemoveGuildMember removeGuildMember(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(removeGuildMember));
}

QVariant
DiscordAPI::guildGetGuildBans(const QVariant &context) {
    GuildGetGuildBans getGuildBans(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildBans));
}

QVariant
DiscordAPI::guildGetGuildBan(const QVariant &context) {
    GuildGetGuildBan getGuildBan(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildBan));
}

QVariant
DiscordAPI::guildCreateGuildBan(const QVariant &context) {
    GuildCreateGuildBan createGuildBan(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createGuildBan));
}

QVariant
DiscordAPI::guildRemoveGuildBan(const QVariant &context) {
    GuildRemoveGuildBan removeGuildBan(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(removeGuildBan));
}

QVariant
DiscordAPI::guildGetGuildRoles(const QVariant &context) {
    GuildGetGuildRoles getGuildRoles(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildRoles));
}

QVariant
DiscordAPI::guildCreateGuildRole(const QVariant &context) {
    GuildCreateGuildRole createGuildRole(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createGuildRole));
}

QVariant
DiscordAPI::guildModifyGuildRolePosition(const QVariant &context) {
    GuildModifyGuildRolePosition modifyGuildRolePosition(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildRolePosition));
}

QVariant
DiscordAPI::guildModifyGuildRole(const QVariant &context) {
    GuildModifyGuildRole modifyGuildRole(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildRole));
}

QVariant
DiscordAPI::guildDeleteGuildRole(const QVariant &context) {
    GuildDeleteGuildRole modifyGuildRole(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildRole));
}

QVariant
DiscordAPI::guildGetGuildPruneCount(const QVariant &context) {
    GuildGetGuildPruneCount getGuildPruneCount(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildPruneCount));
}

QVariant
DiscordAPI::guildBeginGuildPrune(const QVariant &context) {
    GuildBeginGuildPrune beginGuildPrune(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(beginGuildPrune));
}

QVariant
DiscordAPI::guildGetGuildVoiceRegions(const QVariant &context) {
    GuildGetGuildVoiceRegions getGuildVoiceRegions(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildVoiceRegions));
}

QVariant
DiscordAPI::guildGetGuildInvites(const QVariant &context) {
    GuildGetGuildInvites getGuildInvites(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildInvites));
}

QVariant
DiscordAPI::guildGetGuildIntegrations(const QVariant &context) {
    GuildGetGuildIntegrations getGuildIntegrations(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildIntegrations));
}

QVariant
DiscordAPI::guildCreateGuildIntegration(const QVariant &context) {
    GuildCreateGuildIntegration createGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createGuildIntegration));
}

QVariant
DiscordAPI::guildModifyGuildIntegration(const QVariant &context) {
    GuildModifyGuildIntegration modifyGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildIntegration));
}

QVariant
DiscordAPI::guildDeleteGuildIntegration(const QVariant &context) {
    GuildDeleteGuildIntegration deleteGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteGuildIntegration));
}

QVariant
DiscordAPI::guildSyncGuildIntegration(const QVariant &context) {
    GuildSyncGuildIntegration syncGuildIntegration(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(syncGuildIntegration));
}

QVariant
DiscordAPI::guildGetGuildWidget(const QVariant &context) {
    GuildGetGuildWidget getGuildWidget(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildWidget));
}

QVariant
DiscordAPI::guildGetGuildEmbed(const QVariant &context) {
    GuildGetGuildEmbed getGuildEmbed(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildEmbed));
}

QVariant
DiscordAPI::guildModifyGuildWidget(const QVariant &context) {
    GuildModifyGuildWidget modifyGuildWidget(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildWidget));
}

QVariant
DiscordAPI::guildModifyGuildEmbed(const QVariant &context) {
    GuildModifyGuildEmbed modifyGuildEmbed(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildEmbed));
}

QVariant
DiscordAPI::guildGetVanityUrl(const QVariant &context) {
    GuildGetVanityUrl getVanityUrl(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getVanityUrl));
}

QVariant
DiscordAPI::guildGetWidgetImage(const QVariant &context) {
    GuildGetWidgetImage getWidgetImage(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getWidgetImage));
}

QVariant
DiscordAPI::emojiListGuildEmojis(const QVariant &context) {
    EmojiListGuildEmojis listGuildEmojis(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(listGuildEmojis));
}

QVariant
DiscordAPI::emojiCreateGuildEmoji(const QVariant &context) {
    EmojiCreateGuildEmoji createGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createGuildEmoji));
}


QVariant
DiscordAPI::emojiDeleteGuildEmoji(const QVariant &context) {
    EmojiDeleteGuildEmoji deleteGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(deleteGuildEmoji));
}

QVariant
DiscordAPI::emojiGetGuildEmoji(const QVariant &context) {
    EmojiGetGuildEmoji getGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getGuildEmoji));
}

QVariant
DiscordAPI::emojiModifyGuildEmoji(const QVariant &context) {
    EmojiModifyGuildEmoji modifyGuildEmoji(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyGuildEmoji));
}

QVariant
DiscordAPI::userGetCurrentUser(const QVariant &context) {
    UserGetCurrentUser getCurrentUser(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getCurrentUser));
}

QVariant
DiscordAPI::userGetUser(const QVariant &context) {
    UserGetUser getUser(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getUser));
}

QVariant
DiscordAPI::userModifyCurrentUser(const QVariant &context) {
    UserModifyCurrentUser modifyCurrentUser(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(modifyCurrentUser));
}

QVariant
DiscordAPI::userGetCurrentUserGuilds(const QVariant &context) {
    UserCurrentGetUserGuilds getUserGuilds(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getUserGuilds));
}

QVariant
DiscordAPI::userGetUserDms(const QVariant &context) {
    UserGetUserDms getUserDms(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getUserDms));
}

QVariant
DiscordAPI::userLeaveGuild(const QVariant &context) {
    UserLeaveGuild leaveGuild(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(leaveGuild));
}


QVariant
DiscordAPI::userCreateDm(const QVariant &context) {
    UserCreateDm createDm(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(createDm));
}


QVariant
DiscordAPI::userGetUserConnections(const QVariant &context) {
    UserGetUserConnections getUserConnections(buildRequestContext(context));

    return buildResponseVariant(_httpClient.processRoute(getUserConnections));
}
