#ifndef SCRIPTFACTORY_H
#define SCRIPTFACTORY_H

#include "qml/botscript.h"
#include "logging/logfactory.h"
#include "scriptregistrar.h"

#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>

class ScriptFactory : public QObject
{
    Q_OBJECT

    QString _scriptDir;
    QString _botToken;

    Logger *_logger;

    QQmlApplicationEngine _engine;

    QMap<QString, QString> _scriptNameByCommand;
    QSet<QString> _registeredNames;
    QMap<QString, QPair<QString, QSharedPointer<BotScript>>> _registry;

    bool isBotScript(const QString &fileName);
    void initEngine();
    void loadScripts(const QString &scriptDir);
    void loadScriptComponent(const QString &fileName);


public:
    ScriptFactory() { initEngine(); }
    ScriptFactory(const QString &botToken, const QString &scriptDir) {
        _botToken = botToken;
        _scriptDir = scriptDir;
        initEngine();
    }
    ScriptFactory(const ScriptFactory &other) { Q_UNUSED(other) }
    ~ScriptFactory() {}
    const static QString BOT_IMPORT_IDENTIFIER;
    const static QString BOT_TYPE_IDENTIFIER;
    const static QString BOT_API_MINOR_VERSION;
    const static QString BOT_API_MAJOR_VERSION;

    void init(const QString &botToken, const QString &scriptDir = "./scripts");

    QSharedPointer<ScriptRegistrar> buildRegistrar();
};

Q_DECLARE_METATYPE(ScriptFactory)

#endif // SCRIPT_H
