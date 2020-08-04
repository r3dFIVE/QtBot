#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>

#include "bot.h"
#include "logging/logfactory.h"
#include "qml/botscript.h"
#include "entity/guildentity.h"

class Bot;

class CommandFactory : public QObject
{
    Q_OBJECT

    Bot *_bot;
    Logger *_logger;

    QQmlApplicationEngine _engine;
    QString _scriptDir;
    QString _botToken;
    QStringList _coreCommandNames;
    QSet<QString> _registeredScriptNames;
    QMap<QString, QPair<QString, QSharedPointer<IBotJob>>> _registry;
    QMap<QString, QString> _scriptNameByCommand;

    bool isBotScript(const QString &fileName);
    void loadCoreCommands();
    void loadScripts(const QString &scriptDir);
    void loadScriptComponent(const QString &fileName);

    const static QString BOT_IMPORT_IDENTIFIER;
    const static QString BOT_TYPE_IDENTIFIER;
    const static QString BOT_API_MINOR_VERSION;
    const static QString BOT_API_MAJOR_VERSION;

public:

    CommandFactory() {}
    CommandFactory(const CommandFactory &other) { Q_UNUSED(other) }
    ~CommandFactory() {}
    CommandFactory(Bot *bot, const QString &scriptDir, const QString &botToken) {
        _bot = bot;

        _logger = LogFactory::getLogger();

        _scriptDir = scriptDir;

        _botToken = botToken;

        _engine.installExtensions(QJSEngine::ConsoleExtension);

        qmlRegisterType<BotScript>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                                   BOT_API_MAJOR_VERSION.toInt(),
                                   BOT_API_MINOR_VERSION.toInt(),
                                   BOT_TYPE_IDENTIFIER.toUtf8());
    }

    void init(const QString &botToken, const QString &scriptDir);

    QSharedPointer<GuildEntity> buildCommands(QSharedPointer<GuildEntity> guild);
};

Q_DECLARE_METATYPE(CommandFactory)

#endif // COMMANDFACTORY_H
