#ifndef SCRIPTFACTORY_H
#define SCRIPTFACTORY_H

#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>

#include "bot.h"
#include "commandregistrar.h"
#include "logging/logfactory.h"
#include "qml/botscript.h"

class Bot;

class RegistrarFactory : public QObject
{
    Q_OBJECT

    Bot *_bot;
    HttpClient *_httpClient;
    Logger *_logger;

    QQmlApplicationEngine _engine;
    QString _scriptDir;
    QString _botToken;
    QStringList _coreCommandNames;
    QSet<QString> _registeredScriptNames;
    QMap<QString, QPair<QString, QSharedPointer<ICommand>>> _registry;
    QMap<QString, QString> _scriptNameByCommand;

    bool isBotScript(const QString &fileName);
    void initEngine();
    void loadCoreCommands();
    void loadScripts(const QString &scriptDir);
    void loadScriptComponent(const QString &fileName);

    const static QString BOT_IMPORT_IDENTIFIER;
    const static QString BOT_TYPE_IDENTIFIER;
    const static QString BOT_API_MINOR_VERSION;
    const static QString BOT_API_MAJOR_VERSION;

public:

    RegistrarFactory() {}
    RegistrarFactory(Bot *bot, const QString &scriptDir, const QString &botToken) {
        _bot = bot;
        _logger = LogFactory::getLogger();
        _scriptDir = scriptDir;
        _botToken = botToken;
        initEngine();
    }
    RegistrarFactory(const RegistrarFactory &other) { Q_UNUSED(other) }
    ~RegistrarFactory() {}

    void init(const QString &botToken, const QString &scriptDir);

    QSharedPointer<CommandRegistrar> buildRegistrar();
};

Q_DECLARE_METATYPE(RegistrarFactory)

#endif // SCRIPT_H
