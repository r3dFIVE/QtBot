#include "botscript.h"

#include <QSqlError>
#include <QThread>

#include "util/serializationutils.h"
#include "util/enumutils.h"
#include "timedbinding.h"

BotScript::BotScript() {
    _logger = LogFactory::getLogger();
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

    _discordAPI = other._discordAPI;

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

    _discordAPI = other._discordAPI;

    _scriptName = other._scriptName;

    _query = other._query;

    return *this;
}

void
BotScript::setEngine(QSharedPointer<QQmlEngine> engine) {
    _engine = engine;
}

QVariant
BotScript::buildResponseVariant(QSharedPointer<EventContext> apiResponse) {
    QVariant repsonseContext;

    if (apiResponse) {
        repsonseContext = SerializationUtils::toVariant(*apiResponse);
    }

    return repsonseContext;
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





QMap<QString, QVariant>
BotScript::getScriptCommands() const {
    return _commands;
}

QString
BotScript::getScriptName() const {
    return _scriptName;
}

void BotScript::initAPI(const QString &botToken) {
    _discordAPI = QSharedPointer<DiscordAPI>(new DiscordAPI(botToken));
}



QVariant
BotScript::cCreateMessage(const QVariant &contextVariant) {
    EventContext context;

    SerializationUtils::fromVariant(context, contextVariant);

    return buildResponseVariant(_discordAPI->channelCreateMessage(context));
}
