#include "qml/botscript.h"
#include "qml/bsqldatabase.h"
#include "scriptfactory.h"
#include "scriptregistrar.h"

#include "payloads/message.h"
#include "util/jsonutils.h"

#include <QDir>
#include <QFile>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QVariant>


const QString ScriptFactory::BOT_IMPORT_IDENTIFIER = "BotApi";
const QString ScriptFactory::BOT_API_MAJOR_VERSION = "0";
const QString ScriptFactory::BOT_API_MINOR_VERSION = "1";
const QString ScriptFactory::BOT_TYPE_IDENTIFIER = "BotScript";


void
ScriptFactory::initEngine() {
    qmlRegisterType<BotScript>(BOT_IMPORT_IDENTIFIER.toUtf8(), BOT_API_MAJOR_VERSION.toInt(),
                               BOT_API_MINOR_VERSION.toInt(), BOT_TYPE_IDENTIFIER.toUtf8());



    QJSValue bsqlDatabase = _engine.newQMetaObject(&BSqlDatabase::staticMetaObject);

    _engine.globalObject().setProperty("BSqlDatabase", bsqlDatabase);

    _engine.installExtensions(QJSEngine::ConsoleExtension);
}


QSharedPointer<ScriptRegistrar>
ScriptFactory::buildRegistrar() {
    _registry.clear();

    loadScripts(_scriptDir);

    QSharedPointer<ScriptRegistrar> registrar(new ScriptRegistrar);

    registrar->setRegistry(_registry);

    return registrar;
}

void
ScriptFactory::loadScripts(const QString &scriptDir) {
    QDir directory(scriptDir);
    QStringList scripts = directory.entryList(QStringList() << "*.*", QDir::Files);

    for (QString fileName : scripts) {
        QString fileWithPath = scriptDir + fileName;
        if (isBotScript(fileWithPath)) {
            qDebug() << fileName << " is a Bot Script!";
            loadScriptComponent(fileWithPath);
        }
    }
}

void
ScriptFactory::loadScriptComponent(const QString &fileName) {



    QQmlComponent comp(&_engine, "C:\\workspace\\scripts\\BotScript.qml");

    if (comp.errors().size() > 0) {
        qDebug() << comp.errors();
        return;
    }

    QSharedPointer<BotScript> botScript = QSharedPointer<BotScript>(qobject_cast<BotScript*>(comp.create()));

    // TODO remove when httpclient is its own thread
    botScript->setToken(_botToken);

    if (comp.errors().size() > 0) {
        qDebug() << comp.errors();
        return;
    }

    QString scriptName = botScript->name();

    if (_registeredNames.contains(botScript->name())) {
        QFileInfo info(fileName);
        qDebug() << QString("%1 already registered. Please update name property for %2 and reload.")
                    .arg(botScript->name()).arg(info.fileName());
    }

    for (QString command : botScript->commands().keys()) {
        if (_registry.contains(command)) {
            QString existingScript = _registry[command].first;

            qDebug() << QString("Commmand \"%1\" already registered to bot script named: %2")
                        .arg(command).arg(existingScript);
            qDebug() << QString("You must rename \"%1\" before it will be enabled.");
        } else {
            QString mapping = botScript->findMapping(command);
            _registry[command] = qMakePair(mapping, botScript);
            _registeredNames << scriptName;
        }
    }
}

bool
ScriptFactory::isBotScript(const QString &fileName) {
    QFile scriptCandidate(fileName);

    if(!scriptCandidate.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << QString("Failed to open %1, reason: %2")
                    .arg(fileName).arg(scriptCandidate.errorString());
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

    qDebug().noquote() << QString("%1 is not a Bot Script. Did you forget to \"import %2 %3.%4\"?")
                .arg(fileName).arg(BOT_IMPORT_IDENTIFIER).arg(BOT_API_MAJOR_VERSION).arg(BOT_API_MINOR_VERSION);
    return false;
}




