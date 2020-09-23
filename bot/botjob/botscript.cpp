#include "botscript.h"

#include <QSqlError>
#include <QThread>

#include "util/serializationutils.h"
#include "util/enumutils.h"
#include "timedbinding.h"

BotScript::BotScript() {
    _logger = LogFactory::getLogger();

    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI);
}

BotScript::~BotScript() {
    _engine->clearComponentCache();
}

BotScript::BotScript(const BotScript &other) {
    _guildId = other._guildId;

    _database = other._database;

    _logger = other._logger;

    _databaseContext = other._databaseContext;

    _commands = other._commands;

    _scriptName = other._scriptName;

    _query = other._query;
}

BotScript
&BotScript::operator=(const BotScript &other)
{
    _guildId = other._guildId;

    _database = other._database;

    _logger = other._logger;

    _databaseContext = other._databaseContext;

    _commands = other._commands;

    _scriptName = other._scriptName;

    _query = other._query;

    return *this;
}

void
BotScript::setEngine(QSharedPointer<QQmlEngine> engine) {
    _engine = engine;
}

void
BotScript::setEventBindingsJson(const QJsonArray &eventBindingsJson) {
    _eventBindingsJson = eventBindingsJson;
}

QJsonArray
BotScript::getEventBindingsJson() const {
    return _eventBindingsJson;
}

bool
BotScript::invokable() {
    bool canLock = _runLock.tryLock();

    if (canLock) {
        _runLock.unlock();
    }

    return canLock;
}

QString
BotScript::findFunctionMapping(const QString &command) const {
    return _commands[command].toString();
}

void
BotScript::setScriptName(const QString &scriptName) {
    _scriptName = scriptName;
}

void
BotScript::setScriptCommands(const QMap<QString, QVariant> &commands) {
    _commands = commands;
}

void
BotScript::execute(const QByteArray &command, const EventContext &context) {
    QMutexLocker lock(&_runLock);

    QVariant returnValue;

    QMetaObject::invokeMethod(this, command,
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, returnValue),
                              Q_ARG(QVariant, SerializationUtils::toVariant(context)));
}

void
BotScript::queueTimedEvent(const QVariant &timedBindingVariant) {
    QJsonObject binding = QJsonObject::fromVariantMap(timedBindingVariant.toMap());

    QSharedPointer<TimedBinding> timedBinding = QSharedPointer<TimedBinding>(new TimedBinding);

    timedBinding->setFunctionMapping(qMakePair(binding[TimedBinding::FUNCTION].toString(), this));

    timedBinding->setScriptName(_scriptName);

    timedBinding->setRepeatAfter(binding[TimedBinding::REPEAT_AFTER].toInt());

    timedBinding->setSingleShot(binding[TimedBinding::SINGLE_SHOT].toBool());

    timedBinding->setEventContext(binding[TimedBinding::EVENT_CONTEXT].toObject());

    timedBinding->setDescription(binding[IBinding::DESCRIPTION].toString());

    if (timedBinding->isValid(*this->metaObject())) {
       emit timedBindingReady(_guildId, timedBinding);
    }
}

void
BotScript::pause(int ms) {
    QThread::msleep(ms);
}

QMap<QString, QVariant>
BotScript::getScriptCommands() const {
    return _commands;
}

QString
BotScript::getScriptName() const {
    return _scriptName;
}

void
BotScript::logTrace(QString event) {
    _logger->trace(event);
}

void
BotScript::logInfo(QString event) {
    _logger->info(event);
}

void
BotScript::logDebug(QString event) {
    _logger->debug(event);
}

void
BotScript::logWarning(QString event) {
    _logger->warning(event);
}

void
BotScript::logCritical(QString event) {
    _logger->critical(event);
}

void
BotScript::logFatal(QString event) {
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
BotScript::cCreateMessage(const QVariant &context) {
    return _discordAPI->channelCreateMessage(context);
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
