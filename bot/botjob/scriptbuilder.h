#ifndef SCRIPTBUILDER_H
#define SCRIPTBUILDER_H

#include <QObject>
#include <QVariantMap>
#include <QQmlApplicationEngine>

#include "bot.h"
#include "commandbinding.h"
#include "gatewaybinding.h"
#include "timedbinding.h"
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
    QQmlEngine _engine;
    QString _botToken;
    QString _fileName;
    QString _guildId;
    QString _scriptDir;
    QStringList _coreCommandNames;
    QList<CommandBinding> _commandBindings;
    QList<GatewayBinding> _gatewayBindings;
    QList<TimedBinding> _timedBindings;
    QMap<QString, QString> _scriptNameByCommand;
    QMap<QString, QMap<QString, QString> > _functionNameByEventNameByScriptName;

    bool isBotScript(const QString &fileName);
    bool validateScriptCommandName(const QString &command);
    void loadCoreCommands();
    void builldBotScripts(const QString &scriptDir);
    void buildBotScript();
    void namingConflict(const QString &command);
    void validateScriptName(QSharedPointer<BotScript> botScript);
    void resgisterScriptCommands(QSharedPointer<BotScript> botScript);
    void registerCommandBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding);
    void registerGatewayBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding);
    void registerTimedBinding(QSharedPointer<BotScript> botScript, const QJsonValue &binding);
    void registerEventBindings(QSharedPointer<BotScript> botScript);

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
