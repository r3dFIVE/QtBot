#include "scriptbuilder.h"

#include <QDir>
#include <QFile>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QMutableListIterator>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QVariant>

#include "botjob/botscript.h"
#include "botjob/ibinding.h"
#include "payloads/eventcontext.h"
#include "botjob/corecommands.h"
#include "payloads/message.h"
#include "util/enumutils.h"
#include "util/serializationutils.h"


const QString ScriptBuilder::BOT_IMPORT_IDENTIFIER = "BotApi";
const QString ScriptBuilder::BOT_API_MAJOR_VERSION = "0";
const QString ScriptBuilder::BOT_API_MINOR_VERSION = "1";
const QString ScriptBuilder::BOT_TYPE_IDENTIFIER = "BotScript";

QSharedPointer<GuildEntity>
ScriptBuilder::buildCommands(QSharedPointer<GuildEntity> guildEntity) {
    _commandBindings.clear();

    _gatewayBindings.clear();

    _scriptNameByCommand.clear();

    _guildId = guildEntity->id();

    loadCoreCommands();

    builldBotScripts(_scriptDir);

    guildEntity->setCommandBindings(_commandBindings);

    guildEntity->setGatewayBindings(_gatewayBindings);

    return guildEntity;
}

void
ScriptBuilder::loadCoreCommands() {
    QList<CommandBinding> coreCommands = CoreCommands::buildCoreCommandBindings(*_bot, _guildId);

    for (auto coreCommand : coreCommands) {
        _coreCommandNames << coreCommand.getCommandName();
    }

    _commandBindings << coreCommands;
}

void
ScriptBuilder::builldBotScripts(const QString &scriptDir) {
    QDir directory(scriptDir);

    QStringList scripts = directory.entryList(QStringList() << "*.*", QDir::Files);

    for (QString fileName : scripts) {
        QString fileWithPath = scriptDir + fileName;

        if (isBotScript(fileWithPath)) {
            _logger->debug(QString("Loading bot script: %1").arg(fileName));

            _fileName = fileWithPath;

            buildBotScript();
        }
    }
}

void
ScriptBuilder::buildBotScript() {
    _engine.clearComponentCache();

    QQmlComponent comp(&_engine, _fileName);

    if (comp.errors().size() > 0) {
        _logger->debug(comp.errorString());

        return;
    }

    QSharedPointer<BotScript> botScript = QSharedPointer<BotScript>(qobject_cast<BotScript*>(comp.create()));

    if (comp.errors().size() > 0) {
        _logger->debug(comp.errorString());

        return;
    }

    if (botScript->getEventBindingsJson().isEmpty() && botScript->getScriptCommands().isEmpty()) {
        _logger->debug(QString("No Script Commands or Event Bindings set for \"%1\", skipping.")
                       .arg(_fileName));

        return;
    }

    validateScriptName(botScript);

    resgisterScriptCommands(botScript);

    registerEventBindings(botScript);

    botScript->initAPI(_botToken);

    botScript->setGuildId(_guildId);

    botScript->setDatabaseContext(_defaultDatabaseContext);
}

void
ScriptBuilder::validateScriptName(QSharedPointer<BotScript> botScript) {
    if (_scriptNameByCommand.values().contains(botScript->getScriptName())) {
        QFileInfo info(_fileName);

        _logger->warning(QString("%1 already registered. Please update name property for %2 and reload.")
                    .arg(botScript->getScriptName())
                    .arg(info.fileName()));
    }
}

void
ScriptBuilder::resgisterScriptCommands(QSharedPointer<BotScript> botScript) {
    for (QString command : botScript->getScriptCommands().keys()) {

        if (!validateScriptCommandName(command)) {
            return;
        }

        QString functionName = botScript->findFunctionMapping(command);

        IBotJob::FunctionMapping functionMapping = qMakePair(functionName, botScript);

        CommandBinding commandBinding(command, functionMapping);

        if (commandBinding.isValid(*botScript->metaObject())) {
            _scriptNameByCommand[command] = botScript->getScriptName();

            _commandBindings << commandBinding;
        }
    }
}

bool
ScriptBuilder::validateScriptCommandName(const QString &command) {
    if (_coreCommandNames.contains(command)) {
        _logger->warning(QString("Commmand \"%1\" already registered as a core bot command.")
                    .arg(command));

        namingConflict(command);

        return false;

    } else if (_scriptNameByCommand.contains(command)) {
        QString existingScript = _scriptNameByCommand[command];

        _logger->warning(QString("Commmand \"%1\" already registered to bot script named: %2")
                    .arg(command)
                    .arg(existingScript));

        namingConflict(command);

        return false;
    }

    return true;
}

void
ScriptBuilder::namingConflict(const QString &command) {
    _logger->warning(QString("You must rename \"%1\" in %2 before it will be enabled.")
                .arg(command)
                .arg(_fileName));
}

void
ScriptBuilder::registerEventBindings(QSharedPointer<BotScript> botScript) {
    for (QJsonValue binding : botScript->getEventBindingsJson()) {
        QString eventType = binding[IBinding::BINDING_TYPE].toString();

        if (QString::compare(eventType, IBinding::BINDING_TYPE_COMMAND, Qt::CaseInsensitive) == 0) {
            registerCommandBinding(botScript, binding);

        } else if (QString::compare(eventType, IBinding::BINDING_TYPE_GATEWAY, Qt::CaseInsensitive) == 0) {
            registerGatewayBinding(botScript, binding);

        } else if (QString::compare(eventType, IBinding::BINDING_TYPE_TIMED, Qt::CaseInsensitive) == 0) {
            registerTimedBinding(botScript, binding);

        } else {
            _logger->warning(QString("Invalid binding_type: %1").arg(eventType));
        }
    }
}

void
ScriptBuilder::registerCommandBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding) {
    QString command = binding[CommandBinding::COMMAND].toString();

    if (!validateScriptCommandName(command)) {
        return;
    }

    CommandBinding commandBinding;

    commandBinding.setCommandName(command);

    QString functionName = binding[IBinding::FUNCTION].toString();

    commandBinding.setFunctionMapping(qMakePair(functionName, botScript));

    commandBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    if (commandBinding.isValid(*botScript->metaObject())) {
        _scriptNameByCommand[command] = botScript->getScriptName();

        _commandBindings << commandBinding;
    }
}

void
ScriptBuilder::registerGatewayBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding) {
    QString gatewayEventName = binding[GatewayBinding::GATEWAY_EVENT].toString();

    QString functionName = binding[IBinding::FUNCTION].toString();

    if (_functionNameByEventNameByScriptName[botScript->getScriptName()][gatewayEventName] == functionName) {
        _logger->warning(QString("Gateway event \"%1\" has already been registered to function \"\"... Discarding Binding.")
                         .arg(gatewayEventName)
                         .arg(functionName));

        return;
    }

    GatewayBinding gatewayBinding;

    gatewayBinding.setEventName(gatewayEventName);

    gatewayBinding.setFunctionMapping(qMakePair(functionName, botScript));

    gatewayBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    if (gatewayBinding.isValid(*botScript->metaObject())) {
        if (!_functionNameByEventNameByScriptName.contains(botScript->getScriptName())) {
            QMap<QString, QString> functionNameByEventName;

            functionNameByEventName[gatewayEventName] = functionName;

            _functionNameByEventNameByScriptName[botScript->getScriptName()] = functionNameByEventName;

            _gatewayBindings << gatewayBinding;

        } else {
            _functionNameByEventNameByScriptName[botScript->getScriptName()][gatewayEventName] = functionName;

            _gatewayBindings << gatewayBinding;
        }
    }
}

void
ScriptBuilder::registerTimedBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding) {

}

bool
ScriptBuilder::isBotScript(const QString &fileName) {
    QFile scriptCandidate(fileName);

    if(!scriptCandidate.open(QIODevice::ReadOnly | QIODevice::Text)) {
        _logger->warning(QString("Failed to open %1, reason: %2")
                    .arg(fileName)
                    .arg(scriptCandidate.errorString()));

        return false;
    }

    while (!scriptCandidate.atEnd()) {
        QString line = scriptCandidate.readLine().simplified();

        QStringList lineTokens = line.split(" ");

        if (lineTokens[0] != "import") {
            continue;
        }

        if (lineTokens[1] != BOT_IMPORT_IDENTIFIER) {
            continue;
        }

        QString majorMinorVersion = QString("%1.%2").arg(BOT_API_MAJOR_VERSION).arg(BOT_API_MINOR_VERSION);

        if (lineTokens[2] != majorMinorVersion) {
            continue;
        }

        return true;
    }

    _logger->trace(QString("%1 is not a Bot Script. Did you forget to \"import %2 %3.%4\"?")
                .arg(fileName)
                .arg(BOT_IMPORT_IDENTIFIER)
                .arg(BOT_API_MAJOR_VERSION)
                .arg(BOT_API_MINOR_VERSION));

    return false;
}
