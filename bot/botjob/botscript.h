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
#include "ibinding.h"
#include "ibotjob.h"
#include "httpclient.h"
#include "payloads/eventcontext.h"
#include "routes/discordapi.h"
#include "util/globals.h"


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
    void closeExistingConnection();
    void setConnectionName();
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
    Q_ENUM(ParamType)

    BotScript() { _logger = LogFactory::getLogger(); }
    BotScript(QSharedPointer<Settings> settings);
    ~BotScript() {}
    BotScript(const BotScript &other);

    BotScript &operator=(const BotScript &other);

    DatabaseContext getDatabaseContext() const;
    QMap<QString, QVariant> getScriptCommands() const;
    QJsonArray getEventBindingsJson() const;
    QString getScriptName() const;
    QString findFunctionMapping(const QString &command) const;
    void initAPI(const QString &botToken);
    void postResult(const Message &message);
    void setConnectionName(const QString &scriptName, const QString &getGuildId);
    void setDatabaseContext(const DatabaseContext &databaseContext);
    void setEngine(QSharedPointer<QQmlEngine> engine);
    void setScriptName(const QString &scriptName);

    bool invokable() override;
    void execute(const QByteArray &command, const EventContext &message) override;

public slots:
    /*
     *  General API related functions
     */
    void pause(int ms);
    void logTrace(QString event);
    void logInfo(QString event);
    void logDebug(QString event);
    void logWarning(QString event);
    void logCritical(QString event);
    void logFatal(QString event);

    /*
     *  QSqlDatabase related functions
     */
    bool dbOpen();
    void dbClose();
    bool dbIsOpen() const;
    bool dbIsOpenError() const;
    QStringList dbTables(TableType type = Tables) const;
    QString dbLastDatabaseError() const;
    bool dbIsDatabaseValid() const;
    bool dbTransaction();
    bool dbCommit();
    bool dbRollback();
    void dbSetDatabaseName(const QString &name);
    void dbSetUserName(const QString &name);
    void dbSetPassword(const QString &dbPassword);
    void dbSetHostName(const QString &host);
    void dbSetPort(int p);
    void dbSetConnectOptions(const QString &options = QString());
    QString dbDatabaseName() const;
    QString dbUserName() const;
    QString dbHostName() const;
    QString dbDriverName() const;
    int dbPort() const;
    QString dbConnectOptions() const;
    QString dbConnectionName() const;
    void dbSetNumericalPrecisionPolicy(const NumericalPrecisionPolicy &precisionPolicy);
    NumericalPrecisionPolicy dbNumericalPrecisionPolicy() const;
    void dbSetType(const QString &type);
    QStringList dbDrivers();
    bool dbIsDriverAvailable(const QString &name);

    /*
     *  QSqlQuery related functions
     */
    bool qryIsValid() const;
    bool qryIsActive() const;
    bool qryIsNull(int field) const;
    bool qryIsNull(const QString &name) const;
    int qryAt() const;
    QString qryLastQuery() const;
    int qryNumRowsAffected() const;
    QString qryLastError() const;
    bool qryIsSelect() const;
    int qrySize() const;
    bool qryIsForwardOnly() const;
    void qrySetForwardOnly(bool forward);
    bool qryExec(const QString& query);
    QVariant qryValue(int i) const;
    QVariant qryValue(const QString& name) const;
    void qrySetNumericalPrecisionPolicy(NumericalPrecisionPolicy precisionPolicy);
    NumericalPrecisionPolicy qryNumericalPrecisionPolicy() const;
    bool qrySeek(int i, bool relative = false);
    bool qryNext();
    bool qryPrevious();
    bool qryFirst();
    bool qryLast();
    void qryClear();

    // prepared query support
    bool qryExec();
    bool execBatch(BatchExecutionMode mode = ValuesAsRows);
    bool qryPrepare(const QString& query);
    void qryBindValue(const QString& placeholder, const QVariant& val, ParamType type = In);
    void qryBindValue(int pos, const QVariant& val, ParamType type = In);
    void qryAddBindValue(const QVariant& val, ParamType type = In);
    QVariant qryBoundValue(const QString& placeholder) const;
    QVariant qryBoundValue(int pos) const;
    QMap<QString, QVariant> boundValues() const;
    QString qryExecutedQuery() const;
    QVariant qryLastInsertId() const;
    void qryFinish();
    bool qryNextResult();


    /*
     *  DiscordAPI related functions
     */

    // Channel API functions.
    // https://discord.com/developers/docs/resources/channel

    QVariant cCreateMessage(const QVariant &contextVariant);
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
