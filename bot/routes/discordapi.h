/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DISCORDAPI_H
#define DISCORDAPI_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QQmlEngine>

#include "httpclient.h"


class DiscordAPI : public QObject
{
    Q_OBJECT

    static QString _botToken;

    HttpClient _httpClient;

    EventContext buildRequestContext(const QVariant &contextVariant);
    QVariant buildResponseVariant(QSharedPointer<EventContext> apiResponse);

public:        
    DiscordAPI() : _httpClient(_botToken) { }
    ~DiscordAPI() {}

    static QString getBotToken();
    static void setBotToken(const QString &botToken);

    /*
     *      CHANNEL API FUNCTIONS
     *      https://discord.com/developers/docs/resources/channel
     */

    QVariant channelGetChannel(const QVariant &context);
    QVariant channelModifyChannel(const QVariant &context);
    QVariant channelDeleteChannel(const QVariant &context);
    QVariant channelGetChannelMessages(const QVariant &context);
    QVariant channelGetChannelMessage(const QVariant &context);
    QVariant channelCreateMessage(const QVariant &context);
    QVariant channelCrosspostMessage(const QVariant &context);
    QVariant channelCreateReaction(const QVariant &context);
    QVariant channelDeleteOwnReaction(const QVariant &context);
    QVariant channelDeleteUserReaction(const QVariant &context);
    QVariant channelGetReactions(const QVariant &context);
    QVariant channelDeleteAllReactions(const QVariant &context);
    QVariant channelDeleteAllReactionsForEmoji(const QVariant &context);
    QVariant channelEditMessage(const QVariant &context);
    QVariant channelDeleteMessage(const QVariant &context);
    QVariant channelBulkDeleteMessages(const QVariant &context);
    QVariant channelEditChannelPermissions(const QVariant &context);
    QVariant channelGetChannelInvites(const QVariant &context);
    QVariant channelCreateChannelInvite(const QVariant &context);
    QVariant channelDeleteChannelPermission(const QVariant &context);
    QVariant channelFollowNewsChannel(const QVariant &context);
    QVariant channelTriggerTypingIndicator(const QVariant &context);
    QVariant channelGetPinnedMessages(const QVariant &context);
    QVariant channelAddPinnedChannelMessage(const QVariant &context);
    QVariant channelDeletePinnedChannelMessage(const QVariant &context);
    QVariant channelGroupDmAddRecipient(const QVariant &context);
    QVariant channelGroupDmRemoveRecipient(const QVariant &context);

    /*
     *      GUILD API FUNCTIONS
     *      https://discord.com/developers/docs/resources/guild
     */

    QVariant guildCreateGuild(const QVariant &context);
    QVariant guildGetGuild(const QVariant &context);
    QVariant guildGetGuildPreview(const QVariant &context);
    QVariant guildModifyGuild(const QVariant &context);
    QVariant guildDeleteGuild(const QVariant &context);
    QVariant guildGetGuildChannels(const QVariant &context);
    QVariant guildCreateGuildChannel(const QVariant &context);
    QVariant guildModifyGuildChannelPosition(const QVariant &context);
    QVariant guildGetGuildMember(const QVariant &context);
    QVariant guildListGuildMembers(const QVariant &context);
    QVariant guildAddGuildMember(const QVariant &context);
    QVariant guildModifyGuildMember(const QVariant &context);
    QVariant guildModifyCurrentUserNick(const QVariant &context);
    QVariant guildAddGuildMemberRole(const QVariant &context);
    QVariant guildRemoveGuildMemberRole(const QVariant &context);
    QVariant guildRemoveGuildMember(const QVariant &context);
    QVariant guildGetGuildBans(const QVariant &context);
    QVariant guildGetGuildBan(const QVariant &context);
    QVariant guildCreateGuildBan(const QVariant &context);
    QVariant guildRemoveGuildBan(const QVariant &context);
    QVariant guildGetGuildRoles(const QVariant &context);
    QVariant guildCreateGuildRole(const QVariant &context);
    QVariant guildModifyGuildRolePosition(const QVariant &context);
    QVariant guildModifyGuildRole(const QVariant &context);
    QVariant guildDeleteGuildRole(const QVariant &context);
    QVariant guildGuildPruneCount(const QVariant &context);
    QVariant guildGetGuildPruneCount(const QVariant &context);
    QVariant guildBeginGuildPrune(const QVariant &context);
    QVariant guildGetGuildVoiceRegions(const QVariant &context);
    QVariant guildGetGuildInvites(const QVariant &context);
    QVariant guildGetGuildIntegrations(const QVariant &context);
    QVariant guildCreateGuildIntegration(const QVariant &context);
    QVariant guildModifyGuildIntegration(const QVariant &context);
    QVariant guildDeleteGuildIntegration(const QVariant &context);
    QVariant guildSyncGuildIntegration(const QVariant &context);
    QVariant guildGetGuildWidget(const QVariant &context);
    QVariant guildGetGuildWidgetSettings(const QVariant &context);
    QVariant guildGetGuildEmbed(const QVariant &context);
    QVariant guildModifyGuildWidget(const QVariant &context);
    QVariant guildModifyGuildEmbed(const QVariant &context);
    QVariant guildGetVanityUrl(const QVariant &context);
    QVariant guildGetWidgetImage(const QVariant &context);

    /*
     *      EMOJI API FUNCTIONS
     *      https://discord.com/developers/docs/resources/emoji
     */

    QVariant emojiListGuildEmojis(const QVariant &context);
    QVariant emojiCreateGuildEmoji(const QVariant &context);
    QVariant emojiDeleteGuildEmoji(const QVariant &context);
    QVariant emojiGetGuildEmoji(const QVariant &context);
    QVariant emojiModifyGuildEmoji(const QVariant &context);

    /*
     *      USER API FUNCTIONS
     *      https://discord.com/developers/docs/resources/emoji
     */

    QVariant userGetCurrentUser(const QVariant &context);
    QVariant userGetUser(const QVariant &context);
    QVariant userModifyCurrentUser(const QVariant &context);
    QVariant userGetCurrentUserGuilds(const QVariant &context);
    QVariant userGetUserDms(const QVariant &context);
    QVariant userLeaveGuild(const QVariant &context);
    QVariant userCreateDm(const QVariant &context);
    QVariant userGetUserConnections(const QVariant &context);

    /*
     *      WEBHOOK API FUNCTIONS
     *      https://discord.com/developers/docs/resources/webhook
     */

    QVariant webhookCreateWebhook(const QVariant &context);
    QVariant webhookGetChannelWebhooks(const QVariant &context);
    QVariant webhookGetGuildWebhooks(const QVariant &context);
    QVariant webhookGetWebhook(const QVariant &context);
    QVariant webhookGetWebhookWithToken(const QVariant &context);
    QVariant webhookModifyWebhook(const QVariant &context);
    QVariant webhookModifyWebhookWithToken(const QVariant &context);
    QVariant webhookDeleteWebhook(const QVariant &context);
    QVariant webhookDeleteWebhookWithToken(const QVariant &context);
    QVariant webhookExecuteWebhook(const QVariant &context);
    QVariant webhookExecuteSlackCompatibleWebhook(const QVariant &context);
    QVariant webhookExecuteGithubCompatibleWebhook(const QVariant &context);

    /*
     *      INVITE API FUNCTIONS
     *      https://discord.com/developers/docs/resources/invite
     */

    QVariant inviteGetInvite(const QVariant &context);
    QVariant inviteDeleteInvite(const QVariant &context);

    /*
     *      VOICE API FUNCTIONS
     *      https://discord.com/developers/docs/resources/voice
     */

    QVariant voiceListVoiceRegions(const QVariant &context);

};

#endif // DISCORDAPI_H
