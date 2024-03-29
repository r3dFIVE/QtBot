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

#include "scriptmanager.h"

#include <functional>
#include <QQmlComponent>
#include <QMutableListIterator>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QVariant>

#include "bindingfactory.h"
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


ScriptManager::ScriptManager(EventHandler *eventHandler) {
    _defaultDatabaseContext.init();

    _eventHandler = eventHandler;

    _logger = LogFactory::getLogger(this);

    _scriptDir = Settings::scriptDirectory();

    validateScripts();
}

ScriptManager::~ScriptManager() {
    _logger->trace("freeing all scripts");

    _managedScripts.clear();
}

void
ScriptManager::buildScripts(QSharedPointer<GuildEntity> guildEntity, bool validate) {
    if (validate || _validScripts.size() == 0) {
        validateScripts();
    }
    
    guildEntity->clearBindings();

    _managedScripts[guildEntity->getId()].clear();

    buildValidBotScripts(*guildEntity);    

    emit guildReady(guildEntity);
}

void
ScriptManager::validateScripts() {
    _validScripts.clear();

    _commandBindings.clear();

    _gatewayBindings.clear();

    _scriptNamesByCommand.clear();

    _timedBindings.clear();

    for (auto& binding : CoreCommands::buildCoreCommandBindings(*_eventHandler, GuildEntity::DEFAULT_GUILD_ID)) {
        _coreCommandNames << binding->getName();

        _scriptNamesByCommand[binding->getName()] = QString();

        delete binding->getFunctionMapping().second;
    }

    QDir directory(_scriptDir);

    directory.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    for (QFileInfo& fileInfo : directory.entryInfoList()) {

        if (isBotScript(fileInfo.absoluteFilePath())) {
            _logger->debug(QString("Validating bot script: %1").arg(fileInfo.fileName()));

            validate(fileInfo);
        }
    }
}

void
ScriptManager::validate(const QFileInfo &fileInfo) {
    QQmlEngine validator;

    QQmlComponent comp(&validator, fileInfo.absoluteFilePath());

    if (comp.errors().size() > 0) {
        _logger->warning(comp.errorString());

        return;
    }

    BotScript *botScript = qobject_cast<BotScript*>(comp.create());

    if (comp.errors().size() > 0) {
        _logger->warning(comp.errorString());

        return;
    }

    if (botScript->getEventBindingsJson().isEmpty() && botScript->getScriptCommands().isEmpty()) {
        _logger->warning(QString("No Script Commands or Event Bindings set for \"%1\", skipping.")
                       .arg(fileInfo.absoluteFilePath()));

        return;
    }

    QString fileName = fileInfo.fileName();

    if (!validateScriptName(botScript->getName(), fileName)) {
        return;
    }

    for (QString& command : botScript->getScriptCommands().keys()) {
        if (!validateScriptCommandName(command, fileName)) {
            return;
        }
    }

    if (!validateScriptCommands(botScript)) {
        return;
    }

    for (QJsonValue binding : botScript->getEventBindingsJson()) {
        QString eventType = binding[IBinding::BINDING_TYPE].toString();

        if (QString::compare(eventType, IBinding::BINDING_TYPE_COMMAND, Qt::CaseInsensitive) == 0) {
            if (!validateCommandBinding(botScript, binding)) {
                return;
            }            

        } else if (QString::compare(eventType, IBinding::BINDING_TYPE_GATEWAY, Qt::CaseInsensitive) == 0) {
            if (!validateGatewayBinding(botScript, binding)) {
                return;
            }

        } else if (QString::compare(eventType, IBinding::BINDING_TYPE_TIMED, Qt::CaseInsensitive) == 0) {
            if (!validateTimedBinding(botScript, binding)) {
                return;
            }

        } else {
            _logger->warning(QString("Invalid binding_type: %1, for script: %2")
                             .arg(eventType)
                             .arg(botScript->getName()));

            return;
        }
    }

    _validScripts << fileInfo;

    delete botScript;
}

bool
ScriptManager::validateScriptCommands(BotScript *botScript) {
    for (QString command : botScript->getScriptCommands().keys()) {

        if (!validateScriptCommandName(command, botScript->getName())) {
            return false;
        }

        QString functionName = botScript->findFunctionMapping(command);

        IBotJob::FunctionMapping functionMapping = qMakePair(functionName, botScript);

        QSharedPointer<IBindingProperties> baseProperties = QSharedPointer<IBindingProperties>(new IBindingProperties);

        QSharedPointer<CommandBinding> binding =
                QSharedPointer<CommandBinding>(new CommandBinding(command, functionMapping, baseProperties));

        if (!binding->isValid(*botScript->metaObject())) {
            return false;
        }

        _scriptNamesByCommand[command] = botScript->getName();

        _commandBindings[botScript->getName()] << binding;
    }

    return true;
}

bool
ScriptManager::validateCommandBinding(BotScript *botScript, const QJsonValue &jsonBinding) {

    if (!jsonBinding[CommandBinding::ADMIN_ONLY].isUndefined()
            && !jsonBinding[CommandBinding::ADMIN_ONLY].isBool()) {
        _logger->debug(QString("admin_only is not a valid boolean value"));

        return false;
    }

    if (!jsonBinding[CommandBinding::IGNORE_ADMIN].isUndefined()
            && !jsonBinding[CommandBinding::IGNORE_ADMIN].isBool()) {
        _logger->debug(QString("ignore_admin is not a valid boolean value"));

        return false;
    }

    QSharedPointer<CommandBinding> commandBinding = QSharedPointer<CommandBinding>(new CommandBinding);

    BindingFactory::build(*commandBinding, botScript, jsonBinding);

    if (!validateScriptCommandName(commandBinding->getName(), botScript->getName())) {
        return false;
    }

    if (!commandBinding->isValid(*botScript->metaObject())) {
        return false;
    }       

    _scriptNamesByCommand[commandBinding->getName()] = botScript->getName();

    _commandBindings[botScript->getName()] << commandBinding;

    return true;
}

bool
ScriptManager::validateGatewayBinding(BotScript *botScript, const QJsonValue &jsonBinding) {

    if (!jsonBinding[GatewayBinding::IGNORE_ADMIN].isUndefined()
            && !jsonBinding[GatewayBinding::IGNORE_ADMIN].isBool()) {
        _logger->debug(QString("ignore_admin is not a valid boolean value"));

        return false;
    }

    QSharedPointer<GatewayBinding> gatewayBinding = QSharedPointer<GatewayBinding>(new GatewayBinding);

    BindingFactory::build(*gatewayBinding, botScript, jsonBinding);

    QString eventName = gatewayBinding->getEventName();

    QString functionName = gatewayBinding->getFunctionMapping().first;

    if (!validateScriptCommandName(gatewayBinding->getName(), botScript->getName())) {
        return false;
    }

    if (!gatewayBinding->isValid(*botScript->metaObject())) {
        return false;
    }

    _gatewayBindings[botScript->getName()] << gatewayBinding;

    return true;
}

bool
ScriptManager::validateTimedBinding(BotScript *botScript,
                                    const QJsonValue &jsonBinding) {

    if (!jsonBinding[TimedBinding::SINGLE_SHOT].isUndefined() && !jsonBinding[TimedBinding::SINGLE_SHOT].isBool()) {
        _logger->debug(QString("single_shot is not a valid boolean value"));

        return false;
    }

    if (!jsonBinding[TimedBinding::SINGLETON].isUndefined() && !jsonBinding[TimedBinding::SINGLETON].isBool()) {
        _logger->debug(QString("singleton is not a valid boolean value"));

        return false;
    }

    if (!jsonBinding[TimedBinding::FORCE_ENABLE].isUndefined() && !jsonBinding[TimedBinding::FORCE_ENABLE].isBool()) {
        _logger->debug(QString("force_enable is not a valid boolean value"));

        return false;
    }

    QSharedPointer<TimedBinding> timedBinding = QSharedPointer<TimedBinding>(new TimedBinding);

    BindingFactory::build(*timedBinding, botScript, jsonBinding);

    if (!validateScriptCommandName(timedBinding->getName(), botScript->getName())) {
        return false;
    }

    if (!timedBinding->isValid(*botScript->metaObject())) {
        return false;
    }    

    _scriptNamesByCommand[timedBinding->getName()] = botScript->getName();

    _timedBindings[botScript->getName()] << timedBinding;

    return true;
}

void
ScriptManager::addCoreCommands(GuildEntity &guildEntity) {
    QHash<CoreCommand*, QSharedPointer<CommandBinding>> coreCommandMappings
            = CoreCommands::buildCoreCommandBindings(*_eventHandler, guildEntity.getId());

    for (auto& key : coreCommandMappings.keys()) {
        guildEntity.addCommandBinding(nullptr, coreCommandMappings[key]);

        _managedScripts[guildEntity.getId()] << QSharedPointer<IBotJob>(key);
    }
}

void
ScriptManager::buildValidBotScripts(GuildEntity &guildEntity) {
    addCoreCommands(guildEntity);

    for (QFileInfo& fileInfo : _validScripts) {
        _logger->info(QString("Loading bot script: %1 for guild_id: %2")
                      .arg(fileInfo.fileName())
                      .arg(guildEntity.getId()));

        buildBotScript(fileInfo.absoluteFilePath(), guildEntity);
    }    
    
    guildEntity.setCommandNamesByScriptName(_scriptNamesByCommand);    
}

void
ScriptManager::buildBotScript(const QFileInfo &fileInfo, GuildEntity &guildEntity) {
    DatabaseContext databaseContext(_defaultDatabaseContext);

    databaseContext.scriptName = fileInfo.fileName();

    databaseContext.guildId = guildEntity.getId();

    QSharedPointer<QQmlEngine> engine = QSharedPointer<QQmlEngine>(new QQmlEngine);

    QmlFactory::buildQmlFactory(engine, databaseContext);

    QQmlComponent comp(engine.data(), fileInfo.absoluteFilePath());

    if (comp.errors().size() > 0) {
        _logger->debug(comp.errorString());

        return;
    }

    BotScript *botScript = qobject_cast<BotScript*>(comp.create());

    if (comp.errors().size() > 0) {
        _logger->debug(comp.errorString());

        return;
    }    
    
    for (auto& binding : _commandBindings[botScript->getName()]) {
        guildEntity.addCommandBinding(botScript, buildBinding(binding, botScript));
    }

    for (auto& binding : _gatewayBindings[botScript->getName()]) {
        guildEntity.addGatewayBinding(botScript, buildBinding(binding, botScript));
    }

    for (auto& binding : _timedBindings[botScript->getName()]) {
        if (binding->isSingleton() && guildEntity.getId() != GuildEntity::DEFAULT_GUILD_ID) {
            continue;
        }

        guildEntity.addTimedBinding(botScript, buildBinding(binding, botScript));
    }

    botScript->setGuildId(guildEntity.getId());

    botScript->setEngine(engine);

    botScript->setGuildOwnerId(guildEntity.getGuildOwnerId());

    _managedScripts[guildEntity.getId()] << QSharedPointer<IBotJob>(botScript);

    QObject::connect(botScript, &BotScript::timedBindingReadySignal,
                     _eventHandler, &EventHandler::registerTimedBinding);

    QObject::connect(botScript, &BotScript::removeTimedEventByJobIdSignal,
                     _eventHandler, &EventHandler::removeTimedJobById);
}

bool
ScriptManager::validateScriptName(const QString &scriptName, const QString &fileName) {
    bool isValid = true;

    if (_scriptNamesByCommand.values().contains(scriptName)) {
        _logger->warning(QString("%1 already registered. Please update name property for %2 and reload.")
                    .arg(scriptName)
                    .arg(fileName));

        isValid = false;
    }

    return isValid;
}

bool
ScriptManager::validateScriptCommandName(const QString &command, const QString &scriptName) {
    if (command == scriptName) {
        _logger->warning(QString("Script binding name: %1, must be named different than the script name: %2")
                         .arg(command)
                         .arg(scriptName));

        namingConflict(command, scriptName);

        return false;
    }

    if (command.isEmpty()) {
        _logger->warning(QString("Script Commands or Gateway Binding Names cannot be empty in script %1")
                         .arg(scriptName));

        return false;
    }

    if (_coreCommandNames.contains(command)) {
        _logger->warning(QString("\"%1\" already registered as a core bot command.")
                    .arg(command));

        namingConflict(command, scriptName);

        return false;

    }

    if (_scriptNamesByCommand.contains(command)) {
        QString existingScript = _scriptNamesByCommand[command];

        _logger->warning(QString("\"%1\" already registered to bot script named: %2")
                    .arg(command)
                    .arg(existingScript));

        namingConflict(command, scriptName);

        return false;
    }
    
    return true;
}

void
ScriptManager::namingConflict(const QString &command, const QString &fileName) {
    _logger->warning(QString("You must rename binding: \"%1\", in script: \"%2\" before it will be enabled.")
                .arg(command)
                .arg(fileName));
}

bool
ScriptManager::isBotScript(const QString &fileName) {
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

        QString majorMinorVersion = QString("%1.%2")
                .arg(Bot::BOT_API_MAJOR_VERSION)
                .arg(Bot::BOT_API_MINOR_VERSION);

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
