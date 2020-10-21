#ifndef SCRIPTBUILDER_H
#define SCRIPTBUILDER_H

#include <QObject>
#include <QVariantMap>

#include "bot.h"
#include "commandbinding.h"
#include "eventhandler.h"
#include "gatewaybinding.h"
#include "timedbinding.h"
#include "logging/logfactory.h"
#include "botjob/botscript.h"
#include "entity/guildentity.h"

class Bot;
class EventHandler;

class ScriptBuilder : public QObject
{
    Q_OBJECT

    EventHandler *_eventHandler;
    Logger *_logger;

    DatabaseContext _defaultDatabaseContext;
    QString _fileName;
    QString _guildId;
    QString _scriptDir;
    QStringList _coreCommandNames;
    QList<QSharedPointer<IBotJob> > _registeredScripts;
    QList<CommandBinding> _commandBindings;
    QList<GatewayBinding> _gatewayBindings;
    QList<TimedBinding> _timedBindings;
    QMap<QString, QString> _scriptNamesByCommand;
    QMap<QString, QMap<QString, QString> > _functionNameByEventNameByScriptName;

    bool isBotScript(const QString &fileName);
    bool validateScriptCommandName(const QString &command);
    void loadCoreCommands();
    void addQmlFactory(QSharedPointer<QQmlEngine> engine);
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
    const static int BOT_API_MINOR_VERSION;
    const static int BOT_API_MAJOR_VERSION;
    const static QString FILE_OPEN_MODE_IDENTIFIER;
    const static QString SQL_IDENTIFIER;
    const static QString NO_CREATABLE_ENUM;

    ScriptBuilder(EventHandler *eventHandler, QSharedPointer<Settings> settings);

    void init(const QString &botToken, const QString &scriptDir);

public slots:
    void buildScripts(QSharedPointer<GuildEntity> guild);

signals:
    void guildReady(QSharedPointer<GuildEntity> guild);
};

#endif // SCRIPTBUILDER_H
