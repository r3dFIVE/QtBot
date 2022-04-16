/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef BOTSCRIPT_H
#define BOTSCRIPT_H

#include <QMap>
#include <QObject>
#include <QQmlEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include <QVariantMap>

#include "routes/discordapi.h"
#include "databasecontext.h"
#include "ibotjob.h"
#include "qml/eventcontext.h"
#include "qml/file.h"


class TimedBinding;

class BotScript : public IBotJob
{
    Q_OBJECT

    Logger *_logger;

    DatabaseContext _databaseContext;
    QJsonArray _eventBindingsJson;
    QMap<QString, QVariant> _commands;
    QSharedPointer<DiscordAPI> _discordAPI;
    QSharedPointer<QQmlEngine> _engine;
    QSqlQuery _query;
    QString _name;
    QString _description;
    QString _descriptionShort;

    static QString _botId;
    static QString _botName;

    void setScriptCommands(const QMap<QString, QVariant> &commands);
    void setEventBindingsJson(const QJsonArray &eventBindings);

    Q_PROPERTY(QString name READ getName WRITE setName REQUIRED)
    Q_PROPERTY(QString short_description READ getDescriptionShort WRITE setDescriptionShort)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    Q_PROPERTY(QMap commands READ getScriptCommands WRITE setScriptCommands)
    Q_PROPERTY(QJsonArray event_bindings READ getEventBindingsJson WRITE setEventBindingsJson)

public:
    BotScript();
    BotScript(const BotScript &other);
    ~BotScript();
    BotScript &operator=(const BotScript &other);

    DatabaseContext getDatabaseContext() const;
    QMap<QString, QVariant> getScriptCommands() const;
    QJsonArray getEventBindingsJson() const;
    QString findFunctionMapping(const QString &command) const;
    void setDatabaseContext(const DatabaseContext &databaseContext);
    void setEngine(QSharedPointer<QQmlEngine> engine);
    void execute(const QByteArray &command, const EventContext &message) override;
    void setName(const QString &name);
    void setDescription(const QString &description);
    void setDescriptionShort(const QString &description);
    QString getDescription() const;
    QString getDescriptionShort() const;
    QString getName() const;

    static void setBotId(const QString &botId);
    static void setBotName(const QString &botName);

    /*
     *  GENERAL BOT API RELATED FUNCTIONS
     */

    Q_INVOKABLE QVariant bQueueTimedEvent(const QVariant &timedBindingVariant);
    Q_INVOKABLE QString bId() const;
    Q_INVOKABLE QVariant bGetEventContext();
    Q_INVOKABLE void bLogTrace(QString logEvent);
    Q_INVOKABLE void bLogInfo(QString logEvent);
    Q_INVOKABLE void bLogDebug(QString logEvent);
    Q_INVOKABLE void bLogWarning(QString logEvent);
    Q_INVOKABLE void bLogCritical(QString logEvent);
    Q_INVOKABLE void bLogFatal(QString event);
    Q_INVOKABLE QString bName() const;
    Q_INVOKABLE void bPause(int ms);
    Q_INVOKABLE void bRemoveTimedEventByJobId(const QVariant &eventContextVariant);
    Q_INVOKABLE QString bGenerateSHA256(const QString &inputString) const;
    Q_INVOKABLE QString bGenerateSHA256(File *inputFile) const;

    /*
     *  DiscordAPI RELATED FUNCTIONS
     */

    /*
     *  CHANNEL API FUNCTIONS
     *  https://discord.com/developers/docs/resources/channel
     */

    Q_INVOKABLE QVariant cGetChannel(const QVariant &eventContext);
    Q_INVOKABLE QVariant cModifyChannel(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeleteChannel(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGetChannelMessages(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGetChannelMessage(const QVariant &eventContext);
    Q_INVOKABLE QVariant cCreateMessage(const QVariant &eventContext, const QVariantList &files = QVariantList());
    Q_INVOKABLE QVariant cCreateMessage(const QVariant &eventContext, File *file);
    Q_INVOKABLE QVariant cCrosspostMessage(const QVariant &eventContext);
    Q_INVOKABLE QVariant cCreateReaction(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeleteOwnReaction(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeleteUserReaction(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGetReactions(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeleteAllReactions(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeleteAllReactionsForEmoji(const QVariant &eventContext);
    Q_INVOKABLE QVariant cEditMessage(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeleteMessage(const QVariant &eventContext);
    Q_INVOKABLE QVariant cBulkDeleteMessages(const QVariant &eventContext);
    Q_INVOKABLE QVariant cEditChannelPermissions(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGetChannelInvites(const QVariant &eventContext);
    Q_INVOKABLE QVariant cCreateChannelInvite(const QVariant &eventContext);
    Q_INVOKABLE QVariant cFollowNewsChannel(const QVariant &eventContext);
    Q_INVOKABLE QVariant cTriggerTypingIndicator(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGetPinnedMessages(const QVariant &eventContext);
    Q_INVOKABLE QVariant cAddPinnedChannelMessage(const QVariant &eventContext);
    Q_INVOKABLE QVariant cDeletePinnedChannelMessage(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGroupDmAddRecipient(const QVariant &eventContext);
    Q_INVOKABLE QVariant cGroupDmRemoveRecipient(const QVariant &eventContext);

    /*
     *  GUILD API FUNCTIONS
     *  https://discord.com/developers/docs/resources/guild
     */

    Q_INVOKABLE QVariant gCreateGuild(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuild(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildPreview(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuild(const QVariant &eventContext);
    Q_INVOKABLE QVariant gDeleteGuild(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildChannels(const QVariant &eventContext);
    Q_INVOKABLE QVariant gCreateGuildChannel(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildChannelPosition(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildMember(const QVariant &eventContext);
    Q_INVOKABLE QVariant gListGuildMembers(const QVariant &eventContext);
    Q_INVOKABLE QVariant gAddGuildMember(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildMember(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyCurrentUserNick(const QVariant &eventContext);
    Q_INVOKABLE QVariant gAddGuildMemberRole(const QVariant &eventContext);
    Q_INVOKABLE QVariant gRemoveGuildMemberRole(const QVariant &eventContext);
    Q_INVOKABLE QVariant gRemoveGuildMember(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildBans(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildBan(const QVariant &eventContext);
    Q_INVOKABLE QVariant gCreateGuildBan(const QVariant &eventContext);
    Q_INVOKABLE QVariant gRemoveGuildBan(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildRoles(const QVariant &eventContext);
    Q_INVOKABLE QVariant gCreateGuildRole(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildRolePosition(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildRole(const QVariant &eventContext);
    Q_INVOKABLE QVariant gDeleteGuildRole(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildPruneCount(const QVariant &eventContext);
    Q_INVOKABLE QVariant gBeginGuildPrune(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildVoiceRegions(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildInvites(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildIntegrations(const QVariant &eventContext);
    Q_INVOKABLE QVariant gCreateGuildIntegration(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildIntegration(const QVariant &eventContext);
    Q_INVOKABLE QVariant gDeleteGuildIntegration(const QVariant &eventContext);
    Q_INVOKABLE QVariant gSyncGuildIntegration(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildWidget(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildWidgetSettings(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetGuildEmbed(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildWidget(const QVariant &eventContext);
    Q_INVOKABLE QVariant gModifyGuildEmbed(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetVanityUrl(const QVariant &eventContext);
    Q_INVOKABLE QVariant gGetWidgetImage(const QVariant &eventContext);

    /*
     *      EMOJI API FUNCTIONS
     *      https://discord.com/developers/docs/resources/emoji
     */

    Q_INVOKABLE QVariant eListGuildEmojis(const QVariant &eventContext);
    Q_INVOKABLE QVariant eCreateGuildEmoji(const QVariant &eventContext);
    Q_INVOKABLE QVariant eDeleteGuildEmoji(const QVariant &eventContext);
    Q_INVOKABLE QVariant eGetGuildEmoji(const QVariant &eventContext);
    Q_INVOKABLE QVariant eModifyGuildEmoji(const QVariant &eventContext);

    /*
     *      USER API FUNCTIONS
     *      https://discord.com/developers/docs/resources/user
     */

    Q_INVOKABLE QVariant uGetCurrentUser(const QVariant &eventContext);
    Q_INVOKABLE QVariant uGetUser(const QVariant &eventContext);
    Q_INVOKABLE QVariant uModifyCurrentUser(const QVariant &eventContext);
    Q_INVOKABLE QVariant uGetCurrentUserGuilds(const QVariant &eventContext);
    Q_INVOKABLE QVariant uGetUserDms(const QVariant &eventContext);
    Q_INVOKABLE QVariant uCreateDm(const QVariant &eventContext);
    Q_INVOKABLE QVariant uLeaveGuild(const QVariant &eventContext);
    Q_INVOKABLE QVariant uGetUserConnections(const QVariant &eventContext);

    /*
     *      WEBHOOK API FUNCTIONS
     *      https://discord.com/developers/docs/resources/webhook
     */

    Q_INVOKABLE QVariant wCreateWebhook(const QVariant &eventContext);
    Q_INVOKABLE QVariant wGetChannelWebhooks(const QVariant &eventContext);
    Q_INVOKABLE QVariant wGetGuildWebhooks(const QVariant &eventContext);
    Q_INVOKABLE QVariant wGetWebhook(const QVariant &eventContext);
    Q_INVOKABLE QVariant wGetWebhookWithToken(const QVariant &eventContext);
    Q_INVOKABLE QVariant wModifyWebhook(const QVariant &eventContext);
    Q_INVOKABLE QVariant wModifyWebhookWithToken(const QVariant &eventContext);
    Q_INVOKABLE QVariant wDeleteWebhook(const QVariant &eventContext);
    Q_INVOKABLE QVariant wDeleteWebhookWithToken(const QVariant &eventContext);
    Q_INVOKABLE QVariant wExecuteWebhook(const QVariant &eventContext);
    Q_INVOKABLE QVariant wExecuteSlackCompatibleWebhook(const QVariant &eventContext);
    Q_INVOKABLE QVariant wExecuteGithubCompatibleWebhook(const QVariant &eventContext);

    /*
     *      INVITE API FUNCTIONS
     *      https://discord.com/developers/docs/resources/invite
     */

    Q_INVOKABLE QVariant iGetInvite(const QVariant &eventContext);
    Q_INVOKABLE QVariant iDeleteInvite(const QVariant &eventContext);

    /*
     *      VOICE API FUNCTIONS
     *      https://discord.com/developers/docs/resources/voice
     */

    Q_INVOKABLE QVariant vListVoiceRegions(const QVariant &eventContext);


signals:
    void timedBindingReadySignal(const QString &guildId, QSharedPointer<TimedBinding> timedBinding);
    void removeTimedEventByJobIdSignal(QSharedPointer<EventContext> context);
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
