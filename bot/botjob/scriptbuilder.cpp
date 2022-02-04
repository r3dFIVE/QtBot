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

#include "scriptbuilder.h"


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
#include "qml/qmlfactory.h"
#include "qml/enums/openmode.h"
#include "qml/enums/sql.h"
#include "routes/discordapi.h"
#include "util/enumutils.h"
#include "util/serializationutils.h"
#include "timedbinding.h"


ScriptBuilder::ScriptBuilder(EventHandler *eventHandler) {
    _defaultDatabaseContext.init();

    _eventHandler = eventHandler;

    _logger = LogFactory::getLogger();

    _scriptDir = Settings::scriptDirectory();

    validateScripts();
}

void
ScriptBuilder::buildScripts(QSharedPointer<GuildEntity> guildEntity, bool validate) {
    if (validate || _validScripts.size() == 0) {
        validateScripts();
    }

    loadCoreCommands(guildEntity->getId());

    buildValidBotScripts(guildEntity->getId());

    guildEntity->setCommandBindings(_commandBindings);

    guildEntity->setGatewayBindings(_gatewayBindings);

    guildEntity->setTimedBindings(_timedBindings);

    guildEntity->setRegisteredScripts(_registeredScripts);

    guildEntity->setCommandNamesByScriptName(_scriptNamesByCommand);

    emit guildReady(guildEntity);

    _commandBindings.clear();

    _gatewayBindings.clear();

    _registeredScripts.clear();

    _scriptNamesByCommand.clear();

    _timedBindings.clear();

    _functionNameByEventNameByScriptName.clear();
}

void
ScriptBuilder::validateScripts() {
    _validScripts.clear();

    loadCoreCommands(GuildEntity::DEFAULT_GUILD_ID);

    QDir directory(_scriptDir);

    directory.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    for (QFileInfo fileInfo : directory.entryInfoList()) {

        if (isBotScript(fileInfo.absoluteFilePath())) {
            _logger->debug(QString("Validating bot script: %1").arg(fileInfo.fileName()));

            validate(fileInfo);
        }
    }

    _commandBindings.clear();

    _gatewayBindings.clear();

    _registeredScripts.clear();

    _scriptNamesByCommand.clear();

    _timedBindings.clear();

    _functionNameByEventNameByScriptName.clear();
}

void
ScriptBuilder::validate(const QFileInfo &fileInfo) {
    QQmlEngine validator;

    QQmlComponent comp(&validator, fileInfo.absoluteFilePath());

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
                       .arg(fileInfo.absoluteFilePath()));

        return;
    }

    if (!validateScriptName(botScript->getScriptName(), fileInfo.absoluteFilePath())) {
        return;
    }

    for (QString command : botScript->getScriptCommands().keys()) {
        if (!validateScriptCommandName(command, fileInfo.absoluteFilePath())) {
            return;
        }
    }

    if (!validateScriptCommands(botScript, fileInfo)) {
        return;
    }

    for (QJsonValue binding : botScript->getEventBindingsJson()) {
        QString eventType = binding[IBinding::BINDING_TYPE].toString();

        if (QString::compare(eventType, IBinding::BINDING_TYPE_COMMAND, Qt::CaseInsensitive) == 0) {
            if (!validateCommandBinding(botScript, binding, fileInfo)) {
                return;
            }

        } else if (QString::compare(eventType, IBinding::BINDING_TYPE_GATEWAY, Qt::CaseInsensitive) == 0) {
            if (!validateGatewayBinding(botScript, binding, fileInfo)) {
                return;
            }

        } else if (QString::compare(eventType, IBinding::BINDING_TYPE_TIMED, Qt::CaseInsensitive) == 0) {
            if (!validateTimedBinding(botScript, binding, GuildEntity::DEFAULT_GUILD_ID)) {
                return;
            }

        } else {
            _logger->warning(QString("Invalid binding_type: %1").arg(eventType));

            return;
        }
    }

    _validScripts << fileInfo;
}

bool
ScriptBuilder::validateScriptCommands(QSharedPointer<BotScript> botScript, const QFileInfo &fileInfo) {
    for (QString command : botScript->getScriptCommands().keys()) {

        if (!validateScriptCommandName(command, fileInfo.absoluteFilePath())) {
            return false;
        }

        QString functionName = botScript->findFunctionMapping(command);

        IBotJob::FunctionMapping functionMapping = qMakePair(functionName, botScript.data());

        CommandBinding commandBinding(command, functionMapping);

        if (commandBinding.isValid(*botScript->metaObject())) {
            _scriptNamesByCommand[command] = botScript->getScriptName();
        } else {
            return false;
        }
    }

    return true;
}

bool
ScriptBuilder::validateCommandBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding, const QFileInfo &fileInfo) {
    QString command = binding[CommandBinding::COMMAND].toString();

    if (!validateScriptCommandName(command, fileInfo.absoluteFilePath())) {
        return false;
    }

    CommandBinding commandBinding;

    commandBinding.setCommandName(command);

    QString functionName = binding[IBinding::FUNCTION].toString();

    commandBinding.setFunctionMapping(qMakePair(functionName, botScript.data()));

    commandBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    commandBinding.setAdminOnly(binding[CommandBinding::ADMIN_ONLY].toBool());

    commandBinding.setIgnoreAdmin(binding[CommandBinding::IGNORE_ADMIN].toBool());

    if (commandBinding.isValid(*botScript->metaObject())) {
        _scriptNamesByCommand[command] = botScript->getScriptName();

    } else {
        return false;
    }

    return true;
}

bool
ScriptBuilder::validateGatewayBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding, const QFileInfo &fileInfo) {

    QString gatewayEventName = binding[GatewayBinding::GATEWAY_EVENT].toString();

    QString functionName = binding[IBinding::FUNCTION].toString();

    if (_functionNameByEventNameByScriptName[botScript->getScriptName()][gatewayEventName] == functionName) {
        _logger->warning(QString("Gateway event \"%1\" has already been registered to function in script: %3... ")
                         .arg(gatewayEventName)
                         .arg(functionName)
                         .arg(fileInfo.absoluteFilePath()));

        return false;
    }

    GatewayBinding gatewayBinding;

    gatewayBinding.setFunctionMapping(qMakePair(functionName, botScript.data()));

    gatewayBinding.setEventName(gatewayEventName);

    QString bindingName = binding[GatewayBinding::BINDING_NAME].toString();

    if (!validateScriptCommandName(bindingName, fileInfo.absoluteFilePath())) {
        return false;
    }

    gatewayBinding.setBindingName(bindingName);

    gatewayBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    if (gatewayBinding.isValid(*botScript->metaObject())) {
        _functionNameByEventNameByScriptName[botScript->getScriptName()][gatewayEventName] = functionName;
    } else {
        return false;
    }

    return true;
}

bool
ScriptBuilder::validateTimedBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding, const QString &guildId) {
    QString functionName = binding[IBinding::FUNCTION].toString();

    if (binding[TimedBinding::SINGLETON].toBool() && guildId != GuildEntity::DEFAULT_GUILD_ID) {
        return false; // Singleton only run on Default Guild ID 0
    }

    TimedBinding timedBinding;

    timedBinding.setId(QUuid::createUuid().toString(QUuid::Id128));

    timedBinding.setFunctionMapping(qMakePair(functionName, botScript.data()));

    timedBinding.setScriptName(botScript->getScriptName());

    timedBinding.setFireAfter(binding[TimedBinding::FIRE_AFTER].toInt());

    if (binding[TimedBinding::SINGLE_SHOT].isBool()) {
        timedBinding.setSingleShot(binding[TimedBinding::SINGLE_SHOT].toBool());
    }

    timedBinding.setEventContext(binding[TimedBinding::CONTEXT].toObject());

    timedBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    return timedBinding.isValid(*botScript->metaObject());
}

void
ScriptBuilder::loadCoreCommands(const QString &guildId) {
    QMap<QSharedPointer<CoreCommand>, CommandBinding> coreCommandMappings = CoreCommands::buildCoreCommandBindings(*_eventHandler, guildId);

    for (auto key : coreCommandMappings.keys()) {
        CommandBinding binding = coreCommandMappings[key];

        _coreCommandNames << binding.getCommandName();

        _commandBindings << binding;

        _registeredScripts << key;
    }
}

void
ScriptBuilder::buildValidBotScripts(const QString &guildId) {
    for (QFileInfo fileInfo : _validScripts) {
        _logger->info(QString("Loading bot script: %1 for guild_id: %2")
                      .arg(fileInfo.fileName())
                      .arg(guildId));

        buildBotScript(fileInfo.absoluteFilePath(), guildId);
    }
}

void
ScriptBuilder::buildBotScript(const QFileInfo &fileInfo, const QString &guildId) {
    DatabaseContext databaseContext(_defaultDatabaseContext);

    databaseContext.scriptName = fileInfo.fileName();

    databaseContext.guildId = guildId;

    QSharedPointer<QQmlEngine> engine = QSharedPointer<QQmlEngine>(new QQmlEngine);

    QmlFactory::buildQmlFactory(engine, databaseContext);

    QQmlComponent comp(engine.data(), fileInfo.absoluteFilePath());

    if (comp.errors().size() > 0) {
        _logger->debug(comp.errorString());

        return;
    }

    QSharedPointer<BotScript> botScript = QSharedPointer<BotScript>(qobject_cast<BotScript*>(comp.create()));

    if (comp.errors().size() > 0) {
        _logger->debug(comp.errorString());

        return;
    }

    resgisterScriptCommands(botScript);

    registerEventBindings(botScript, guildId);

    botScript->setGuildId(guildId);

    botScript->setEngine(engine);

    _registeredScripts << botScript;

    QObject::connect(botScript.data(), &BotScript::timedBindingReadySignal,
                     _eventHandler, &EventHandler::registerTimedBinding);

    QObject::connect(botScript.data(), &BotScript::removeTimedEventByJobIdSignal,
                     _eventHandler, &EventHandler::removeTimedJobById);
}

bool
ScriptBuilder::validateScriptName(const QString &scriptName, const QString &fileName) {
    bool isValid = true;

    if (_scriptNamesByCommand.values().contains(scriptName)) {
        _logger->warning(QString("%1 already registered. Please update name property for %2 and reload.")
                    .arg(scriptName)
                    .arg(fileName));

        isValid = false;
    }

    return isValid;
}

void
ScriptBuilder::resgisterScriptCommands(QSharedPointer<BotScript> botScript) {
    for (QString command : botScript->getScriptCommands().keys()) {

        QString functionName = botScript->findFunctionMapping(command);

        IBotJob::FunctionMapping functionMapping = qMakePair(functionName, botScript.data());

        CommandBinding commandBinding(command, functionMapping);

        _scriptNamesByCommand[command] = botScript->getScriptName();

        _commandBindings << commandBinding;
    }
}

bool
ScriptBuilder::validateScriptCommandName(const QString &command, const QString &fileName) {
    if (command.isEmpty()) {
        _logger->warning(QString("Script Commands or Gateway Binding Names cannot be empty in script %1").arg(fileName));

        return false;
    }

    if (_coreCommandNames.contains(command)) {
        _logger->warning(QString("\"%1\" already registered as a core bot command.")
                    .arg(command));

        namingConflict(command, fileName);

        return false;

    } else if (_scriptNamesByCommand.contains(command)) {
        QString existingScript = _scriptNamesByCommand[command];

        _logger->warning(QString("\"%1\" already registered to bot script named: %2")
                    .arg(command)
                    .arg(existingScript));

        namingConflict(command, fileName);

        return false;
    }

    return true;
}

void
ScriptBuilder::namingConflict(const QString &command, const QString &fileName) {
    _logger->warning(QString("You must rename \"%1\" in %2 before it will be enabled.")
                .arg(command)
                .arg(fileName));
}

void
ScriptBuilder::registerEventBindings(QSharedPointer<BotScript> botScript, const QString &guildId) {
    for (QJsonValue binding : botScript->getEventBindingsJson()) {
        if (binding[GatewayBinding::SINGLETON].toBool() && guildId != GuildEntity::DEFAULT_GUILD_ID) {
            return; // Singleton only run on Default Guild ID 0
        }

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

    CommandBinding commandBinding;

    commandBinding.setCommandName(command);

    QString functionName = binding[IBinding::FUNCTION].toString();

    commandBinding.setFunctionMapping(qMakePair(functionName, botScript.data()));

    commandBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    commandBinding.setAdminOnly(binding[CommandBinding::ADMIN_ONLY].toBool());

    commandBinding.setIgnoreAdmin(binding[CommandBinding::IGNORE_ADMIN].toBool());

    _scriptNamesByCommand[command] = botScript->getScriptName();

    _commandBindings << commandBinding;
}

void
ScriptBuilder::registerGatewayBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding) {
    QString functionName = binding[IBinding::FUNCTION].toString();

    GatewayBinding gatewayBinding;

    gatewayBinding.setFunctionMapping(qMakePair(functionName, botScript.data()));

    QString gatewayEventName = binding[GatewayBinding::GATEWAY_EVENT].toString();

    gatewayBinding.setEventName(gatewayEventName);

    QString bindingName = binding[GatewayBinding::BINDING_NAME].toString();

    gatewayBinding.setBindingName(bindingName);

    gatewayBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    gatewayBinding.setIgnoreAdmin(binding[IBinding::IGNORE_ADMIN].toBool());

    _functionNameByEventNameByScriptName[botScript->getScriptName()][gatewayEventName] = functionName;

    _gatewayBindings << gatewayBinding;
}

void
ScriptBuilder::registerTimedBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding) {
    QString functionName = binding[IBinding::FUNCTION].toString();

    TimedBinding timedBinding;

    timedBinding.setId(QUuid::createUuid().toString(QUuid::Id128));

    timedBinding.setFunctionMapping(qMakePair(functionName, botScript.data()));

    timedBinding.setScriptName(botScript->getScriptName());

    timedBinding.setFireAfter(binding[TimedBinding::FIRE_AFTER].toInt());

    if (binding[TimedBinding::SINGLE_SHOT].isBool()) {
        timedBinding.setSingleShot(binding[TimedBinding::SINGLE_SHOT].toBool());
    }

    timedBinding.setEventContext(binding[TimedBinding::CONTEXT].toObject());

    timedBinding.setDescription(binding[IBinding::DESCRIPTION].toString());

    _timedBindings << timedBinding;
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

        if (lineTokens[1] != Bot::BOT_IMPORT_IDENTIFIER) {
            continue;
        }

        QString majorMinorVersion = QString("%1.%2").arg(Bot::BOT_API_MAJOR_VERSION).arg(Bot::BOT_API_MINOR_VERSION);

        if (lineTokens[2] != majorMinorVersion) {
            continue;
        }

        return true;
    }

    _logger->trace(QString("%1 is not a Bot Script. Did you forget to \"import %2 %3.%4\"?")
                .arg(fileName)
                .arg(Bot::BOT_IMPORT_IDENTIFIER)
                .arg(Bot::BOT_API_MAJOR_VERSION)
                .arg(Bot::BOT_API_MINOR_VERSION));

    return false;
}
