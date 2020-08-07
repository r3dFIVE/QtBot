#include "commandfactory.h"

#include <QDir>
#include <QFile>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QVariant>

#include "qml/botscript.h"
#include "payloads/eventcontext.h"
#include "util/corecommands.h"
#include "payloads/message.h"
#include "util/serializationutils.h"


const QString CommandFactory::BOT_IMPORT_IDENTIFIER = "BotApi";
const QString CommandFactory::BOT_API_MAJOR_VERSION = "0";
const QString CommandFactory::BOT_API_MINOR_VERSION = "1";
const QString CommandFactory::BOT_TYPE_IDENTIFIER = "BotScript";


QSharedPointer<GuildEntity>
CommandFactory::buildCommands(QSharedPointer<GuildEntity> guild) {
    _registry.clear();

    _registeredScriptNames.clear();

    _guildId = guild->id();

    loadCoreCommands();

    loadScripts(_scriptDir);

    guild->setRegistry(_registry);

    return guild;
}

void
CommandFactory::loadCoreCommands() {
    QMap<QString, IBotJob::CommandMapping > coreCommands = CoreCommands::buildCommands(*_bot,_guildId);

    for (QString commandName : coreCommands.keys()) {
        _coreCommandNames << commandName;
    }

    _registry.insert(coreCommands);
}

void
CommandFactory::loadScripts(const QString &scriptDir) {
    QDir directory(scriptDir);

    QStringList scripts = directory.entryList(QStringList() << "*.*", QDir::Files);

    for (QString fileName : scripts) {

        QString fileWithPath = scriptDir + fileName;

        if (isBotScript(fileWithPath)) {

            _logger->debug(QString("Loading bot script: %1").arg(fileName));

            loadScriptComponent(fileWithPath);
        }
    }
}

void
CommandFactory::loadScriptComponent(const QString &fileName) {
    _engine.clearComponentCache();

    QQmlComponent comp(&_engine, fileName);

    if (comp.errors().size() > 0) {

        _logger->debug(comp.errorString());

        return;
    }

    QSharedPointer<BotScript> botScript = QSharedPointer<BotScript>(qobject_cast<BotScript*>(comp.create()));

    botScript->initAPI(_botToken);

    botScript->setGuildId(_guildId);

    if (comp.errors().size() > 0) {

        _logger->debug(comp.errorString());

        return;
    }

    QString scriptName = botScript->getScriptName();

    if (_registeredScriptNames.contains(botScript->getScriptName())) {

        QFileInfo info(fileName);

        _logger->warning(QString("%1 already registered. Please update name property for %2 and reload.")
                    .arg(botScript->getScriptName()).arg(info.fileName()));
    }

    for (QString command : botScript->getScriptCommands().keys()) {
        bool namingConflict = true;

        if (_coreCommandNames.contains(command)) {

            _logger->warning(QString("Commmand \"%1\" already registered as a core bot command.")
                        .arg(command));

        } else if (_registry.contains(command)) {            
            QString existingScript = _registry[command].first;

            _logger->warning(QString("Commmand \"%1\" already registered to bot script named: %2")
                        .arg(command).arg(existingScript));
        } else {

            QString mapping = botScript->findCommandMapping(command);

            _registry[command] = qMakePair(mapping, botScript);

            _registeredScriptNames << scriptName;

            namingConflict = false;
        }

        if (namingConflict) {
            _logger->warning(QString("You must rename \"%1\" in %2 before it will be enabled.")
                        .arg(command).arg(fileName));
        }
    }
}

bool
CommandFactory::isBotScript(const QString &fileName) {
    QFile scriptCandidate(fileName);

    if(!scriptCandidate.open(QIODevice::ReadOnly | QIODevice::Text)) {
        _logger->warning(QString("Failed to open %1, reason: %2")
                    .arg(fileName).arg(scriptCandidate.errorString()));

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

    _logger->trace( QString("%1 is not a Bot Script. Did you forget to \"import %2 %3.%4\"?")
                .arg(fileName).arg(BOT_IMPORT_IDENTIFIER).arg(BOT_API_MAJOR_VERSION).arg(BOT_API_MINOR_VERSION));
    return false;
}




