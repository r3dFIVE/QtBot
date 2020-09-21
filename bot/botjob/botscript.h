#ifndef BOTSCRIPT_H
#define BOTSCRIPT_H

#include <QMap>
#include <QObject>
#include <QQmlEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include <QVariantMap>

#include "databasecontext.h"
#include "ibotjob.h"
#include "httpclient.h"
#include "payloads/eventcontext.h"
#include "routes/discordapi.h"
#include "qml/file.h"
#include "util/globals.h"

class TimedBinding;

class BotScript : public IBotJob
{
    Q_OBJECT

    Logger *_logger;

    DatabaseContext _databaseContext;
    QJsonArray _eventBindingsJson;
    QMap<QString, QVariant> _commands;
    QMutex _runLock;
    QSharedPointer<DiscordAPI> _discordAPI;
    QSharedPointer<QQmlEngine> _engine;
    QSqlDatabase _database;
    QSqlQuery _query;
    QString _scriptName;

    QVariant buildResponseVariant(QSharedPointer<EventContext> apiResponse);

    void setScriptCommands(const QMap<QString, QVariant> &commands);
    void setEventBindingsJson(const QJsonArray &eventBindings);

    Q_PROPERTY(QString name READ getScriptName WRITE setScriptName REQUIRED)
    Q_PROPERTY(QMap commands READ getScriptCommands WRITE setScriptCommands)
    Q_PROPERTY(QJsonArray event_bindings READ getEventBindingsJson WRITE setEventBindingsJson)

public:
    enum TableType {
        Tables          = 1,
        SystemTables    = 2,
        Views           = 4,
        AllTables       = 255
    };
    Q_ENUM(TableType)

    enum NumericalPrecisionPolicy
    {
        LowPrecisionInt32    = 1,
        LowPrecisionInt64    = 2,
        LowPrecisionDouble   = 4,

        HighPrecision        = 0
    };
    Q_ENUM(NumericalPrecisionPolicy)

    enum BatchExecutionMode {
        ValuesAsRows,
        ValuesAsColumns
    };
    Q_ENUM(BatchExecutionMode)

    enum ParamType
    {
        In = 1,
        Out = 2,
        InOut = In | Out,
        Binary = 4
    };
    Q_FLAG(ParamType)


    BotScript();
    BotScript(const BotScript &other);
    ~BotScript();
    BotScript &operator=(const BotScript &other);

    DatabaseContext getDatabaseContext() const;
    QMap<QString, QVariant> getScriptCommands() const;
    QJsonArray getEventBindingsJson() const;
    QString getScriptName() const;
    QString findFunctionMapping(const QString &command) const;
    void initAPI(const QString &botToken);
    void postResult(const Message &message);
    void setDatabaseContext(const DatabaseContext &databaseContext);
    void setEngine(QSharedPointer<QQmlEngine> engine);
    void setScriptName(const QString &scriptName);

    bool invokable() override;
    void execute(const QByteArray &command, const EventContext &message) override;

public slots:
    /*
     *  General API related functions
     */

    void queueTimedEvent(const QVariant &timedBindingVariant);
    void logTrace(QString event);
    void logInfo(QString event);
    void logDebug(QString event);
    void logWarning(QString event);
    void logCritical(QString event);
    void logFatal(QString event);
    void pause(int ms);




    /*
     *  DiscordAPI related functions
     */

    // Channel API functions.
    // https://discord.com/developers/docs/resources/channel

    QVariant cCreateMessage(const QVariant &contextVariant);

signals:
    void timedBindingReady(const QString &guildId, QSharedPointer<TimedBinding> timedBinding);
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
