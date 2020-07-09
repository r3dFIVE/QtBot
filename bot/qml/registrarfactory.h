#ifndef SCRIPTFACTORY_H
#define SCRIPTFACTORY_H

#include "qml/botscript.h"
#include "logging/logfactory.h"
#include "commandregistrar.h"
#include "bot.h"

#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>

class Bot;

class RegistrarFactory : public QObject
{
    Q_OBJECT

    QString _scriptDir;
    QString _botToken;

    Logger *_logger;

    QQmlApplicationEngine _engine;

    QStringList _coreCommandNames;
    QSet<QString> _registeredScriptNames;
    QMap<QString, QPair<QString, QSharedPointer<ICommand>>> _registry;
    QMap<QString, QString> _scriptNameByCommand;

    bool isBotScript(const QString &fileName);
    void initEngine();
    void loadCoreCommands(Bot &bot);
    void loadScripts(const QString &scriptDir);
    void loadScriptComponent(const QString &fileName);


public:
    RegistrarFactory() { initEngine(); }
    RegistrarFactory(const QString &botToken, const QString &scriptDir) {
        _botToken = botToken;
        _scriptDir = scriptDir;
        initEngine();
    }
    RegistrarFactory(const RegistrarFactory &other) { Q_UNUSED(other) }
    ~RegistrarFactory() {}

    const static QString BOT_IMPORT_IDENTIFIER;
    const static QString BOT_TYPE_IDENTIFIER;
    const static QString BOT_API_MINOR_VERSION;
    const static QString BOT_API_MAJOR_VERSION;

    void init(const QString &botToken, const QString &scriptDir = "./scripts");

    QSharedPointer<CommandRegistrar> buildRegistrar(Bot &bot);
};

Q_DECLARE_METATYPE(RegistrarFactory)

#endif // SCRIPT_H
