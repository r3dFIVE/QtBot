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
BotScript::execute(const QByteArray &command, const EventContext &context) {    
    QVariant returnValue;

    QMetaObject::invokeMethod(this, command,
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, returnValue),
                              Q_ARG(QVariant, SerializationUtils::toVariant(context)));

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

    QString uuid = QUuid::createUuid().toString(QUuid::Id128);

    jsonBinding[IBinding::BINDING_NAME] = uuid;

    BindingFactory::build(binding, this, jsonBinding);

    QSharedPointer<TimedBinding> timedBinding
            = QSharedPointer<TimedBinding>(new TimedBinding(binding));

    timedBinding->setId(uuid);

    if (timedBinding->isValid(*this->metaObject())) {
        timedBinding->start();

        emit timedBindingReadySignal(_guildId, timedBinding);
    }

    return timedBinding->id();
}

QString
BotScript::bId() const {
    return _botId;
}

QVariant
BotScript::bGetContext() {
    EventContext context;

    context.setGuildId(_guildId);

    return SerializationUtils::toVariant(context);
}

QString
BotScript::bName() const {
    return _botName;
}

void
BotScript::bRemoveTimedEventByJobId(const QVariant &contextVariant) {
    QSharedPointer<EventContext> context = QSharedPointer<EventContext>(new EventContext);

    SerializationUtils::fromVariant(*context.data(), contextVariant);

    emit removeTimedEventByJobIdSignal(context);
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
BotScript::cGetChannel(const QVariant &context) {
    return _discordAPI->channelGetChannel(context);
}

QVariant
BotScript::cModifyChannel(const QVariant &context) {
    return _discordAPI->channelModifyChannel(context);
}

QVariant
BotScript::cDeleteChannel(const QVariant &context) {
    return _discordAPI->channelDeleteChannel(context);
}

QVariant
BotScript::cGetChannelMessages(const QVariant &context) {
    return _discordAPI->channelGetChannelMessages(context);
}

QVariant
BotScript::cGetChannelMessage(const QVariant &context) {
    return _discordAPI->channelGetChannelMessage(context);
}

QVariant
BotScript::cCreateMessage(const QVariant &context, File *file) {
    QVariantList files;

    if (file) {
        files << QVariant::fromValue(file);
    }

    return _discordAPI->channelCreateMessage(context, files);
}


QVariant
BotScript::cCreateMessage(const QVariant &context, const QVariantList &files) {
    return _discordAPI->channelCreateMessage(context, files);
}

QVariant
BotScript::cCrosspostMessage(const QVariant &context) {
    return _discordAPI->channelCrosspostMessage(context);
}

QVariant
BotScript::cCreateReaction(const QVariant &context) {
    return _discordAPI->channelCreateReaction(context);
}

QVariant
BotScript::cDeleteOwnReaction(const QVariant &context) {
    return _discordAPI->channelDeleteOwnReaction(context);
}

QVariant
BotScript::cDeleteUserReaction(const QVariant &context) {
    return _discordAPI->channelDeleteUserReaction(context);
}

QVariant
BotScript::cGetReactions(const QVariant &context) {
    return _discordAPI->channelGetReactions(context);
}

QVariant
BotScript::cDeleteAllReactions(const QVariant &context) {
    return _discordAPI->channelDeleteAllReactions(context);
}

QVariant
BotScript::cDeleteAllReactionsForEmoji(const QVariant &context) {
    return _discordAPI->channelDeleteAllReactionsForEmoji(context);
}

QVariant
BotScript::cEditMessage(const QVariant &context) {
    return _discordAPI->channelEditMessage(context);
}

QVariant
BotScript::cDeleteMessage(const QVariant &context) {
    return _discordAPI->channelDeleteMessage(context);
}

QVariant
BotScript::cBulkDeleteMessages(const QVariant &context) {
    return _discordAPI->channelDeleteMessage(context);
}

QVariant
BotScript::cEditChannelPermissions(const QVariant &context) {
    return _discordAPI->channelEditChannelPermissions(context);
}

QVariant
BotScript::cGetChannelInvites(const QVariant &context) {
    return _discordAPI->channelGetChannelInvites(context);
}

QVariant
BotScript::cCreateChannelInvite(const QVariant &context) {
    return _discordAPI->channelCreateChannelInvite(context);
}

QVariant
BotScript::cFollowNewsChannel(const QVariant &context) {
    return _discordAPI->channelFollowNewsChannel(context);
}

QVariant
BotScript::cTriggerTypingIndicator(const QVariant &context) {
    return _discordAPI->channelTriggerTypingIndicator(context);
}

QVariant
BotScript::cGetPinnedMessages(const QVariant &context) {
    return _discordAPI->channelGetPinnedMessages(context);
}

QVariant
BotScript::cAddPinnedChannelMessage(const QVariant &context) {
    return _discordAPI->channelAddPinnedChannelMessage(context);
}

QVariant
BotScript::cDeletePinnedChannelMessage(const QVariant &context) {
    return _discordAPI->channelDeletePinnedChannelMessage(context);
}

QVariant
BotScript::cGroupDmAddRecipient(const QVariant &context) {
    return _discordAPI->channelGroupDmAddRecipient(context);
}

QVariant
BotScript::cGroupDmRemoveRecipient(const QVariant &context) {
    return _discordAPI->channelGroupDmRemoveRecipient(context);
}

QVariant
BotScript::gCreateGuild(const QVariant &context) {
    return _discordAPI->guildCreateGuild(context);
}

QVariant
BotScript::gGetGuild(const QVariant &context) {
    return _discordAPI->guildGetGuild(context);
}

QVariant
BotScript::gGetGuildPreview(const QVariant &context) {
    return _discordAPI->guildGetGuild(context);
}

QVariant
BotScript::gModifyGuild(const QVariant &context) {
    return _discordAPI->guildModifyGuild(context);
}

QVariant
BotScript::gDeleteGuild(const QVariant &context) {
    return _discordAPI->guildDeleteGuild(context);
}

QVariant
BotScript::gGetGuildChannels(const QVariant &context) {
    return _discordAPI->guildGetGuildChannels(context);
}

QVariant
BotScript::gCreateGuildChannel(const QVariant &context) {
    return _discordAPI->guildCreateGuildChannel(context);
}

QVariant
BotScript::gModifyGuildChannelPosition(const QVariant &context) {
    return _discordAPI->guildModifyGuildChannelPosition(context);
}

QVariant
BotScript::gGetGuildMember(const QVariant &context) {
    return _discordAPI->guildGetGuildMember(context);
}

QVariant
BotScript::gListGuildMembers(const QVariant &context) {
    return _discordAPI->guildListGuildMembers(context);
}

QVariant
BotScript::gAddGuildMember(const QVariant &context) {
    return _discordAPI->guildAddGuildMember(context);
}

QVariant
BotScript::gModifyGuildMember(const QVariant &context) {
    return _discordAPI->guildModifyGuildMember(context);
}

QVariant
BotScript::gModifyCurrentUserNick(const QVariant &context) {
    return _discordAPI->guildModifyCurrentUserNick(context);
}

QVariant
BotScript::gAddGuildMemberRole(const QVariant &context) {
    return _discordAPI->guildAddGuildMemberRole(context);
}

QVariant
BotScript::gRemoveGuildMemberRole(const QVariant &context) {
    return _discordAPI->guildRemoveGuildMemberRole(context);
}

QVariant
BotScript::gRemoveGuildMember(const QVariant &context) {
    return _discordAPI->guildRemoveGuildMember(context);
}

QVariant
BotScript::gGetGuildBans(const QVariant &context) {
    return _discordAPI->guildGetGuildBans(context);
}

QVariant
BotScript::gGetGuildBan(const QVariant &context) {
    return _discordAPI->guildGetGuildBan(context);
}

QVariant
BotScript::gCreateGuildBan(const QVariant &context) {
    return _discordAPI->guildCreateGuildBan(context);
}

QVariant
BotScript::gRemoveGuildBan(const QVariant &context) {
    return _discordAPI->guildRemoveGuildBan(context);
}

QVariant
BotScript::gGetGuildRoles(const QVariant &context) {
    return _discordAPI->guildGetGuildRoles(context);
}

QVariant
BotScript::gCreateGuildRole(const QVariant &context) {
    return _discordAPI->guildCreateGuildRole(context);
}

QVariant
BotScript::gModifyGuildRolePosition(const QVariant &context) {
    return _discordAPI->guildModifyGuildRolePosition(context);
}

QVariant
BotScript::gModifyGuildRole(const QVariant &context) {
    return _discordAPI->guildModifyGuildRole(context);
}

QVariant
BotScript::gDeleteGuildRole(const QVariant &context) {
    return _discordAPI->guildDeleteGuildRole(context);
}

QVariant
BotScript::gGetGuildPruneCount(const QVariant &context) {
    return _discordAPI->guildGetGuildPruneCount(context);
}

QVariant
BotScript::gBeginGuildPrune(const QVariant &context) {
    return _discordAPI->guildBeginGuildPrune(context);
}

QVariant
BotScript::gGetGuildVoiceRegions(const QVariant &context) {
    return _discordAPI->guildGetGuildVoiceRegions(context);
}

QVariant
BotScript::gGetGuildInvites(const QVariant &context) {
    return _discordAPI->guildGetGuildInvites(context);
}

QVariant
BotScript::gGetGuildIntegrations(const QVariant &context) {
    return _discordAPI->guildGetGuildIntegrations(context);
}

QVariant
BotScript::gCreateGuildIntegration(const QVariant &context) {
    return _discordAPI->guildCreateGuildIntegration(context);
}

QVariant
BotScript::gModifyGuildIntegration(const QVariant &context) {
    return _discordAPI->guildModifyGuildIntegration(context);
}

QVariant
BotScript::gDeleteGuildIntegration(const QVariant &context) {
    return _discordAPI->guildDeleteGuildIntegration(context);
}

QVariant
BotScript::gSyncGuildIntegration(const QVariant &context) {
    return _discordAPI->guildSyncGuildIntegration(context);
}

QVariant
BotScript::gGetGuildWidget(const QVariant &context) {
    return _discordAPI->guildGetGuildWidget(context);
}


QVariant
BotScript::gGetGuildWidgetSettings(const QVariant &context) {
    return _discordAPI->guildGetGuildWidget(context);
}

QVariant
BotScript::gGetGuildEmbed(const QVariant &context) {
    return _discordAPI->guildGetGuildEmbed(context);
}

QVariant
BotScript::gModifyGuildWidget(const QVariant &context) {
    return _discordAPI->guildModifyGuildWidget(context);
}

QVariant
BotScript::gModifyGuildEmbed(const QVariant &context) {
    return _discordAPI->guildModifyGuildEmbed(context);
}

QVariant
BotScript::gGetVanityUrl(const QVariant &context) {
    return _discordAPI->guildGetVanityUrl(context);
}

QVariant
BotScript::gGetWidgetImage(const QVariant &context) {
    return _discordAPI->guildGetWidgetImage(context);
}

QVariant
BotScript::eListGuildEmojis(const QVariant &context) {
    return _discordAPI->emojiListGuildEmojis(context);
}

QVariant
BotScript::eCreateGuildEmoji(const QVariant &context) {
    return _discordAPI->emojiCreateGuildEmoji(context);
}

QVariant
BotScript::eDeleteGuildEmoji(const QVariant &context) {
    return _discordAPI->emojiDeleteGuildEmoji(context);
}

QVariant
BotScript::eGetGuildEmoji(const QVariant &context) {
    return _discordAPI->emojiGetGuildEmoji(context);
}

QVariant
BotScript::eModifyGuildEmoji(const QVariant &context) {
    return _discordAPI->emojiModifyGuildEmoji(context);
}

QVariant
BotScript::uGetCurrentUser(const QVariant &context) {
    return _discordAPI->userGetCurrentUser(context);
}

QVariant
BotScript::uGetUser(const QVariant &context) {
    return _discordAPI->userGetUser(context);
}

QVariant
BotScript::uModifyCurrentUser(const QVariant &context) {
    return _discordAPI->userModifyCurrentUser(context);
}

QVariant
BotScript::uGetCurrentUserGuilds(const QVariant &context) {
    return _discordAPI->userGetCurrentUserGuilds(context);
}

QVariant
BotScript::uGetUserDms(const QVariant &context) {
    return _discordAPI->userGetUserDms(context);
}

QVariant
BotScript::uCreateDm(const QVariant &context) {
    return _discordAPI->userCreateDm(context);
}

QVariant
BotScript::uLeaveGuild(const QVariant &context) {
    return _discordAPI->userLeaveGuild(context);
}

QVariant
BotScript::uGetUserConnections(const QVariant &context) {
    return _discordAPI->userGetUserConnections(context);
}

QVariant
BotScript::wCreateWebhook(const QVariant &context) {
    return _discordAPI->webhookCreateWebhook(context);
}

QVariant
BotScript::wGetChannelWebhooks(const QVariant &context) {
    return _discordAPI->webhookGetChannelWebhooks(context);
}

QVariant
BotScript::wGetGuildWebhooks(const QVariant &context) {
    return _discordAPI->webhookGetGuildWebhooks(context);
}

QVariant
BotScript::wGetWebhook(const QVariant &context) {
    return _discordAPI->webhookGetWebhook(context);
}

QVariant
BotScript::wGetWebhookWithToken(const QVariant &context) {
    return _discordAPI->webhookGetWebhookWithToken(context);
}

QVariant
BotScript::wModifyWebhook(const QVariant &context) {
    return _discordAPI->webhookModifyWebhook(context);
}

QVariant
BotScript::wModifyWebhookWithToken(const QVariant &context) {
    return _discordAPI->webhookModifyWebhookWithToken(context);
}

QVariant
BotScript::wDeleteWebhook(const QVariant &context) {
    return _discordAPI->webhookDeleteWebhook(context);
}

QVariant
BotScript::wDeleteWebhookWithToken(const QVariant &context) {
    return _discordAPI->webhookDeleteWebhookWithToken(context);
}

QVariant
BotScript::wExecuteWebhook(const QVariant &context) {
    return _discordAPI->webhookExecuteWebhook(context);
}

QVariant
BotScript::wExecuteSlackCompatibleWebhook(const QVariant &context) {
    return _discordAPI->webhookExecuteSlackCompatibleWebhook(context);
}

QVariant
BotScript::wExecuteGithubCompatibleWebhook(const QVariant &context) {
    return _discordAPI->webhookExecuteGithubCompatibleWebhook(context);
}

QVariant
BotScript::iGetInvite(const QVariant &context) {
    return _discordAPI->inviteGetInvite(context);
}

QVariant
BotScript::iDeleteInvite(const QVariant &context) {
    return _discordAPI->inviteDeleteInvite(context);
}

QVariant
BotScript::vListVoiceRegions(const QVariant &context) {
    return _discordAPI->voiceListVoiceRegions(context);
}

