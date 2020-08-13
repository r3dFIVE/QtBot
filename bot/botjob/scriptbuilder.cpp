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
#include "util/serializationutils.h"


const QString ScriptBuilder::BOT_IMPORT_IDENTIFIER = "BotApi";
const QString ScriptBuilder::BOT_API_MAJOR_VERSION = "0";
const QString ScriptBuilder::BOT_API_MINOR_VERSION = "1";
const QString ScriptBuilder::BOT_TYPE_IDENTIFIER = "BotScript";

QSharedPointer<GuildEntity>
ScriptBuilder::buildCommands(QSharedPointer<GuildEntity> guildEntity) {
    _commandBindings.clear();

    _scriptNameByCommand.clear();

    _guildId = guildEntity->id();

    loadCoreCommands();

    builldBotScripts(_scriptDir);

    guildEntity->setCommandBindings(_commandBindings);



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

            buildBotScript(fileWithPath);
        }
    }
}

void
ScriptBuilder::buildBotScript(const QString &fileName) {
    _engine.clearComponentCache();

    QQmlComponent comp(&_engine, fileName);

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
                       .arg(fileName));

        return;
    }

    validateScriptName(botScript, fileName);

    validateScriptCommands(botScript, fileName);

    validateEventBindings(botScript, fileName);

    botScript->initAPI(_botToken);

    botScript->setGuildId(_guildId);

    botScript->setDatabaseContext(_defaultDatabaseContext);
}

void
ScriptBuilder::validateScriptName(QSharedPointer<BotScript> botScript, const QString &fileName) {
    if (_scriptNameByCommand.values().contains(botScript->getScriptName())) {
        QFileInfo info(fileName);

        _logger->warning(QString("%1 already registered. Please update name property for %2 and reload.")
                    .arg(botScript->getScriptName())
                    .arg(info.fileName()));
    }
}

void
ScriptBuilder::validateScriptCommands(QSharedPointer<BotScript> botScript, const QString &fileName) {
    for (QString command : botScript->getScriptCommands().keys()) {

        if (_coreCommandNames.contains(command)) {
            _logger->warning(QString("Commmand \"%1\" already registered as a core bot command.")
                        .arg(command));

            namingConflict(command, fileName);

            continue;

        } else if (_scriptNameByCommand.contains(command)) {
            QString existingScript = _scriptNameByCommand[command];

            _logger->warning(QString("Commmand \"%1\" already registered to bot script named: %2")
                        .arg(command)
                        .arg(existingScript));

            namingConflict(command, fileName);

            continue;
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

void
ScriptBuilder::namingConflict(const QString &command, const QString &fileName) {
    _logger->warning(QString("You must rename \"%1\" in %2 before it will be enabled.")
                .arg(command)
                .arg(fileName));
}

void
ScriptBuilder::validateEventBindings(QSharedPointer<BotScript> botScript, const QString &fileName) {


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
