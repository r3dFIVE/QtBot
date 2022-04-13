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

#include "bindingfactory.h"
#include "botscript.h"

#include <QSqlError>
#include <QThread>
#include <QCryptographicHash>

#include "util/serializationutils.h"
#include "util/enumutils.h"
#include "timedbinding.h"
#include "payloads/embed.h"


QString BotScript::_botId = QString();
QString BotScript::_botName = QString();

BotScript::BotScript() {
    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI);
}

BotScript::~BotScript() {
    if (_engine) {
        _engine->clearComponentCache();
    }
}

BotScript::BotScript(const BotScript &other) {
    _guildId = other._guildId;

    _logger = other._logger;

    _commands = other._commands;

    _name = other._name;

    _description = other._description;

    _descriptionShort = other._descriptionShort;
}

BotScript
&BotScript::operator=(const BotScript &other) {    
    if (this == &other) {
        return *this;
    }

    _guildId = other._guildId;

    _logger = other._logger;

    _commands = other._commands;

    _name = other._name;

    _description = other._description;

    _descriptionShort = other._descriptionShort;

    return *this;
}

void
BotScript::setEngine(QSharedPointer<QQmlEngine> engine) {
    _engine = engine;

    _engine->setParent(this);
}

void
BotScript::setEventBindingsJson(const QJsonArray &eventBindingsJson) {
    _eventBindingsJson = eventBindingsJson;
}

QJsonArray
BotScript::getEventBindingsJson() const {
    return _eventBindingsJson;
}

QString
BotScript::findFunctionMapping(const QString &command) const {
    return _commands[command].toString();
}

void
BotScript::setName(const QString &name) {
    _logger = LogFactory::getLogger(name);

    _name = name;
}

void
BotScript::setScriptCommands(const QMap<QString, QVariant> &commands) {
    _commands = commands;
}

void
BotScript::execute(const QByteArray &command, const EventContext &eventContext) {
    QVariant returnValue;

    QMetaObject::invokeMethod(this, command,
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, returnValue),
                              Q_ARG(QVariant, SerializationUtils::toVariant(eventContext)));

    _runLock.unlock();
}

void
BotScript::setDescription(const QString &description) {
    _description = description;
}

void
BotScript::setDescriptionShort(const QString &description) {
    _descriptionShort = description;
}

QString
BotScript::getDescription() const {
    return _description.isEmpty() ? _descriptionShort : _description;
}

QString
BotScript::getDescriptionShort() const {
    QString descriptionShort = _descriptionShort.isEmpty() ? _description : _descriptionShort;

    return descriptionShort.left(Embed::DECRIPTION_SHORT_MAX_LENGTH);
}

QString
BotScript::getName() const {
    return _name;
}

void
BotScript::setBotId(const QString &botId) {
    _botId = botId;
}

void
BotScript::setBotName(const QString &botName) {
    _botName = botName;
}

QVariant
BotScript::bQueueTimedEvent(const QVariant &timedBindingVariant) {
    QJsonObject jsonBinding = QJsonObject::fromVariantMap(timedBindingVariant.toMap());

    TimedBinding binding;

    BindingFactory::build(binding, this, jsonBinding);

    QSharedPointer<TimedBinding> timedBinding
            = QSharedPointer<TimedBinding>(new TimedBinding(binding));

    QString uuid = QUuid::createUuid().toString(QUuid::Id128);

    timedBinding->setId(uuid);

    //timedBinding->setName(uuid);

    if (timedBinding->isValid(*this->metaObject())) {
       emit timedBindingReadySignal(_guildId, timedBinding);
    }

    return timedBinding->id();
}

QString
BotScript::bId() const {
    return _botId;
}

QVariant
BotScript::bGetEventContext() {
    EventContext eventContext;

    eventContext.setGuildId(_guildId);

    return SerializationUtils::toVariant(eventContext);
}

QString
BotScript::bName() const {
    return _botName;
}

void
BotScript::bRemoveTimedEventByJobId(const QVariant &eventContextVariant) {
    QSharedPointer<EventeventContext> eventContext = QSharedPointer<EventeventContext>(new EventeventContext);

    SerializationUtils::fromVariant(*eventContext.data(), eventContextVariant);

    emit removeTimedEventByJobIdSignal(eventContext);
}

QString
BotScript::bGenerateSHA256(const QString &inputString) const {
    return QString(QCryptographicHash::hash(inputString.toUtf8(), QCryptographicHash::Sha256).toHex());
}

QString
BotScript::bGenerateSHA256(File *inputFile) const {
    QSharedPointer<QCryptographicHash> hash = QSharedPointer<QCryptographicHash>(new QCryptographicHash(QCryptographicHash::Sha256));

    hash->addData(inputFile->get());

    return QString(hash->result().toHex());
}

void
BotScript::bPause(int ms) {
    QThread::msleep(ms);
}

QMap<QString, QVariant>
BotScript::getScriptCommands() const {
    return _commands;
}

void
BotScript::bLogTrace(QString event) {
    _logger->trace(event);
}

void
BotScript::bLogInfo(QString event) {
    _logger->info(event);
}

void
BotScript::bLogDebug(QString event) {
    _logger->debug(event);
}

void
BotScript::bLogWarning(QString event) {
    _logger->warning(event);
}

void
BotScript::bLogCritical(QString event) {
    _logger->critical(event);
}

void
BotScript::bLogFatal(QString event) {
    _logger->fatal(event);
}

QVariant
BotScript::cGetChannel(const QVariant &eventContext) {
    return _discordAPI->channelGetChannel(eventContext);
}

QVariant
BotScript::cModifyChannel(const QVariant &eventContext) {
    return _discordAPI->channelModifyChannel(eventContext);
}

QVariant
BotScript::cDeleteChannel(const QVariant &eventContext) {
    return _discordAPI->channelDeleteChannel(eventContext);
}

QVariant
BotScript::cGetChannelMessages(const QVariant &eventContext) {
    return _discordAPI->channelGetChannelMessages(eventContext);
}

QVariant
BotScript::cGetChannelMessage(const QVariant &eventContext) {
    return _discordAPI->channelGetChannelMessage(eventContext);
}

QVariant
BotScript::cCreateMessage(const QVariant &eventContext, File *file) {
    QVariantList files;

    if (file) {
        files << QVariant::fromValue(file);
    }

    return _discordAPI->channelCreateMessage(eventContext, files);
}


QVariant
BotScript::cCreateMessage(const QVariant &eventContext, const QVariantList &files) {
    return _discordAPI->channelCreateMessage(eventContext, files);
}

QVariant
BotScript::cCrosspostMessage(const QVariant &eventContext) {
    return _discordAPI->channelCrosspostMessage(eventContext);
}

QVariant
BotScript::cCreateReaction(const QVariant &eventContext) {
    return _discordAPI->channelCreateReaction(eventContext);
}

QVariant
BotScript::cDeleteOwnReaction(const QVariant &eventContext) {
    return _discordAPI->channelDeleteOwnReaction(eventContext);
}

QVariant
BotScript::cDeleteUserReaction(const QVariant &eventContext) {
    return _discordAPI->channelDeleteUserReaction(eventContext);
}

QVariant
BotScript::cGetReactions(const QVariant &eventContext) {
    return _discordAPI->channelGetReactions(eventContext);
}

QVariant
BotScript::cDeleteAllReactions(const QVariant &eventContext) {
    return _discordAPI->channelDeleteAllReactions(eventContext);
}

QVariant
BotScript::cDeleteAllReactionsForEmoji(const QVariant &eventContext) {
    return _discordAPI->channelDeleteAllReactionsForEmoji(eventContext);
}

QVariant
BotScript::cEditMessage(const QVariant &eventContext) {
    return _discordAPI->channelEditMessage(eventContext);
}

QVariant
BotScript::cDeleteMessage(const QVariant &eventContext) {
    return _discordAPI->channelDeleteMessage(eventContext);
}

QVariant
BotScript::cBulkDeleteMessages(const QVariant &eventContext) {
    return _discordAPI->channelDeleteMessage(eventContext);
}

QVariant
BotScript::cEditChannelPermissions(const QVariant &eventContext) {
    return _discordAPI->channelEditChannelPermissions(eventContext);
}

QVariant
BotScript::cGetChannelInvites(const QVariant &eventContext) {
    return _discordAPI->channelGetChannelInvites(eventContext);
}

QVariant
BotScript::cCreateChannelInvite(const QVariant &eventContext) {
    return _discordAPI->channelCreateChannelInvite(eventContext);
}

QVariant
BotScript::cFollowNewsChannel(const QVariant &eventContext) {
    return _discordAPI->channelFollowNewsChannel(eventContext);
}

QVariant
BotScript::cTriggerTypingIndicator(const QVariant &eventContext) {
    return _discordAPI->channelTriggerTypingIndicator(eventContext);
}

QVariant
BotScript::cGetPinnedMessages(const QVariant &eventContext) {
    return _discordAPI->channelGetPinnedMessages(eventContext);
}

QVariant
BotScript::cAddPinnedChannelMessage(const QVariant &eventContext) {
    return _discordAPI->channelAddPinnedChannelMessage(eventContext);
}

QVariant
BotScript::cDeletePinnedChannelMessage(const QVariant &eventContext) {
    return _discordAPI->channelDeletePinnedChannelMessage(eventContext);
}

QVariant
BotScript::cGroupDmAddRecipient(const QVariant &eventContext) {
    return _discordAPI->channelGroupDmAddRecipient(eventContext);
}

QVariant
BotScript::cGroupDmRemoveRecipient(const QVariant &eventContext) {
    return _discordAPI->channelGroupDmRemoveRecipient(eventContext);
}

QVariant
BotScript::gCreateGuild(const QVariant &eventContext) {
    return _discordAPI->guildCreateGuild(eventContext);
}

QVariant
BotScript::gGetGuild(const QVariant &eventContext) {
    return _discordAPI->guildGetGuild(eventContext);
}

QVariant
BotScript::gGetGuildPreview(const QVariant &eventContext) {
    return _discordAPI->guildGetGuild(eventContext);
}

QVariant
BotScript::gModifyGuild(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuild(eventContext);
}

QVariant
BotScript::gDeleteGuild(const QVariant &eventContext) {
    return _discordAPI->guildDeleteGuild(eventContext);
}

QVariant
BotScript::gGetGuildChannels(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildChannels(eventContext);
}

QVariant
BotScript::gCreateGuildChannel(const QVariant &eventContext) {
    return _discordAPI->guildCreateGuildChannel(eventContext);
}

QVariant
BotScript::gModifyGuildChannelPosition(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildChannelPosition(eventContext);
}

QVariant
BotScript::gGetGuildMember(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildMember(eventContext);
}

QVariant
BotScript::gListGuildMembers(const QVariant &eventContext) {
    return _discordAPI->guildListGuildMembers(eventContext);
}

QVariant
BotScript::gAddGuildMember(const QVariant &eventContext) {
    return _discordAPI->guildAddGuildMember(eventContext);
}

QVariant
BotScript::gModifyGuildMember(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildMember(eventContext);
}

QVariant
BotScript::gModifyCurrentUserNick(const QVariant &eventContext) {
    return _discordAPI->guildModifyCurrentUserNick(eventContext);
}

QVariant
BotScript::gAddGuildMemberRole(const QVariant &eventContext) {
    return _discordAPI->guildAddGuildMemberRole(eventContext);
}

QVariant
BotScript::gRemoveGuildMemberRole(const QVariant &eventContext) {
    return _discordAPI->guildRemoveGuildMemberRole(eventContext);
}

QVariant
BotScript::gRemoveGuildMember(const QVariant &eventContext) {
    return _discordAPI->guildRemoveGuildMember(eventContext);
}

QVariant
BotScript::gGetGuildBans(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildBans(eventContext);
}

QVariant
BotScript::gGetGuildBan(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildBan(eventContext);
}

QVariant
BotScript::gCreateGuildBan(const QVariant &eventContext) {
    return _discordAPI->guildCreateGuildBan(eventContext);
}

QVariant
BotScript::gRemoveGuildBan(const QVariant &eventContext) {
    return _discordAPI->guildRemoveGuildBan(eventContext);
}

QVariant
BotScript::gGetGuildRoles(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildRoles(eventContext);
}

QVariant
BotScript::gCreateGuildRole(const QVariant &eventContext) {
    return _discordAPI->guildCreateGuildRole(eventContext);
}

QVariant
BotScript::gModifyGuildRolePosition(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildRolePosition(eventContext);
}

QVariant
BotScript::gModifyGuildRole(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildRole(eventContext);
}

QVariant
BotScript::gDeleteGuildRole(const QVariant &eventContext) {
    return _discordAPI->guildDeleteGuildRole(eventContext);
}

QVariant
BotScript::gGetGuildPruneCount(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildPruneCount(eventContext);
}

QVariant
BotScript::gBeginGuildPrune(const QVariant &eventContext) {
    return _discordAPI->guildBeginGuildPrune(eventContext);
}

QVariant
BotScript::gGetGuildVoiceRegions(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildVoiceRegions(eventContext);
}

QVariant
BotScript::gGetGuildInvites(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildInvites(eventContext);
}

QVariant
BotScript::gGetGuildIntegrations(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildIntegrations(eventContext);
}

QVariant
BotScript::gCreateGuildIntegration(const QVariant &eventContext) {
    return _discordAPI->guildCreateGuildIntegration(eventContext);
}

QVariant
BotScript::gModifyGuildIntegration(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildIntegration(eventContext);
}

QVariant
BotScript::gDeleteGuildIntegration(const QVariant &eventContext) {
    return _discordAPI->guildDeleteGuildIntegration(eventContext);
}

QVariant
BotScript::gSyncGuildIntegration(const QVariant &eventContext) {
    return _discordAPI->guildSyncGuildIntegration(eventContext);
}

QVariant
BotScript::gGetGuildWidget(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildWidget(eventContext);
}


QVariant
BotScript::gGetGuildWidgetSettings(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildWidget(eventContext);
}

QVariant
BotScript::gGetGuildEmbed(const QVariant &eventContext) {
    return _discordAPI->guildGetGuildEmbed(eventContext);
}

QVariant
BotScript::gModifyGuildWidget(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildWidget(eventContext);
}

QVariant
BotScript::gModifyGuildEmbed(const QVariant &eventContext) {
    return _discordAPI->guildModifyGuildEmbed(eventContext);
}

QVariant
BotScript::gGetVanityUrl(const QVariant &eventContext) {
    return _discordAPI->guildGetVanityUrl(eventContext);
}

QVariant
BotScript::gGetWidgetImage(const QVariant &eventContext) {
    return _discordAPI->guildGetWidgetImage(eventContext);
}

QVariant
BotScript::eListGuildEmojis(const QVariant &eventContext) {
    return _discordAPI->emojiListGuildEmojis(eventContext);
}

QVariant
BotScript::eCreateGuildEmoji(const QVariant &eventContext) {
    return _discordAPI->emojiCreateGuildEmoji(eventContext);
}

QVariant
BotScript::eDeleteGuildEmoji(const QVariant &eventContext) {
    return _discordAPI->emojiDeleteGuildEmoji(eventContext);
}

QVariant
BotScript::eGetGuildEmoji(const QVariant &eventContext) {
    return _discordAPI->emojiGetGuildEmoji(eventContext);
}

QVariant
BotScript::eModifyGuildEmoji(const QVariant &eventContext) {
    return _discordAPI->emojiModifyGuildEmoji(eventContext);
}

QVariant
BotScript::uGetCurrentUser(const QVariant &eventContext) {
    return _discordAPI->userGetCurrentUser(eventContext);
}

QVariant
BotScript::uGetUser(const QVariant &eventContext) {
    return _discordAPI->userGetUser(eventContext);
}

QVariant
BotScript::uModifyCurrentUser(const QVariant &eventContext) {
    return _discordAPI->userModifyCurrentUser(eventContext);
}

QVariant
BotScript::uGetCurrentUserGuilds(const QVariant &eventContext) {
    return _discordAPI->userGetCurrentUserGuilds(eventContext);
}

QVariant
BotScript::uGetUserDms(const QVariant &eventContext) {
    return _discordAPI->userGetUserDms(eventContext);
}

QVariant
BotScript::uCreateDm(const QVariant &eventContext) {
    return _discordAPI->userCreateDm(eventContext);
}

QVariant
BotScript::uLeaveGuild(const QVariant &eventContext) {
    return _discordAPI->userLeaveGuild(eventContext);
}

QVariant
BotScript::uGetUserConnections(const QVariant &eventContext) {
    return _discordAPI->userGetUserConnections(eventContext);
}

QVariant
BotScript::wCreateWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookCreateWebhook(eventContext);
}

QVariant
BotScript::wGetChannelWebhooks(const QVariant &eventContext) {
    return _discordAPI->webhookGetChannelWebhooks(eventContext);
}

QVariant
BotScript::wGetGuildWebhooks(const QVariant &eventContext) {
    return _discordAPI->webhookGetGuildWebhooks(eventContext);
}

QVariant
BotScript::wGetWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookGetWebhook(eventContext);
}

QVariant
BotScript::wGetWebhookWithToken(const QVariant &eventContext) {
    return _discordAPI->webhookGetWebhookWithToken(eventContext);
}

QVariant
BotScript::wModifyWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookModifyWebhook(eventContext);
}

QVariant
BotScript::wModifyWebhookWithToken(const QVariant &eventContext) {
    return _discordAPI->webhookModifyWebhookWithToken(eventContext);
}

QVariant
BotScript::wDeleteWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookDeleteWebhook(eventContext);
}

QVariant
BotScript::wDeleteWebhookWithToken(const QVariant &eventContext) {
    return _discordAPI->webhookDeleteWebhookWithToken(eventContext);
}

QVariant
BotScript::wExecuteWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookExecuteWebhook(eventContext);
}

QVariant
BotScript::wExecuteSlackCompatibleWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookExecuteSlackCompatibleWebhook(eventContext);
}

QVariant
BotScript::wExecuteGithubCompatibleWebhook(const QVariant &eventContext) {
    return _discordAPI->webhookExecuteGithubCompatibleWebhook(eventContext);
}

QVariant
BotScript::iGetInvite(const QVariant &eventContext) {
    return _discordAPI->inviteGetInvite(eventContext);
}

QVariant
BotScript::iDeleteInvite(const QVariant &eventContext) {
    return _discordAPI->inviteDeleteInvite(eventContext);
}

QVariant
BotScript::vListVoiceRegions(const QVariant &eventContext) {
    return _discordAPI->voiceListVoiceRegions(eventContext);
}

