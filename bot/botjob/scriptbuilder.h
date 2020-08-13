#ifndef SCRIPTBUILDER_H
#define SCRIPTBUILDER_H

#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>

#include "bot.h"
#include "commandbinding.h"
#include "logging/logfactory.h"
#include "botjob/botscript.h"
#include "entity/guildentity.h"

class Bot;

class ScriptBuilder : public QObject
{
    Q_OBJECT

    Bot *_bot;
    Logger *_logger;

    DatabaseContext _defaultDatabaseContext;
    QQmlApplicationEngine _engine;
    QString _botToken;
    QString _guildId;
    QString _scriptDir;
    QStringList _coreCommandNames;
    QList<CommandBinding> _commandBindings;
//    QList<GatewayBinding> _gatewayBindings;
//    QList<TimedBinding> _timedBindings;
    QMap<QString, QString> _scriptNameByCommand;

    bool isBotScript(const QString &fileName);
    void loadCoreCommands();
    void builldBotScripts(const QString &scriptDir);
    void buildBotScript(const QString &fileName);
    void namingConflict(const QString &command, const QString &fileName);
    void validateScriptName(QSharedPointer<BotScript> botscript, const QString &fileName);
    void validateScriptCommands(QSharedPointer<BotScript> botscript, const QString &fileName);
    void validateEventBindings(QSharedPointer<BotScript> botscript, const QString &fileName);

public:
    const static QString BOT_IMPORT_IDENTIFIER;
    const static QString BOT_TYPE_IDENTIFIER;
    const static QString BOT_API_MINOR_VERSION;
    const static QString BOT_API_MAJOR_VERSION;

    ScriptBuilder(Bot *bot, QSharedPointer<Settings> settings)
        : _defaultDatabaseContext(settings) {

        _bot = bot;

        _logger = LogFactory::getLogger();

        _scriptDir = settings->value(SettingsParam::Script::SCRIPT_DIRECTORY).toString();

        _botToken = settings->value(SettingsParam::Connection::BOT_TOKEN).toString();;

        _engine.installExtensions(QJSEngine::ConsoleExtension);

        qmlRegisterType<BotScript>(BOT_IMPORT_IDENTIFIER.toUtf8(),
                                   BOT_API_MAJOR_VERSION.toInt(),
                                   BOT_API_MINOR_VERSION.toInt(),
                                   BOT_TYPE_IDENTIFIER.toUtf8());
    }

    QSharedPointer<GuildEntity> buildCommands(QSharedPointer<GuildEntity> guild);
    void init(const QString &botToken, const QString &scriptDir);
};

#endif // SCRIPTBUILDER_H
