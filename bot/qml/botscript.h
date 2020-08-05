#ifndef BOTSCRIPT_H
#define BOTSCRIPT_H

#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include <QVariantMap>

#include "eventcontext.h"
#include "httpclient.h"
#include "botjob/ibotjob.h"
#include "routes/discordapi.h"

class BotScript : public QObject, public IBotJob
{
    Q_OBJECT

    QMutex _runLock;

    QSharedPointer<DiscordAPI> discordAPI;
    QSqlDatabase _database;
    QSqlQuery _query;

    Q_PROPERTY(QString name READ getScriptName WRITE setScriptName REQUIRED)
    QString _name;

    Q_PROPERTY(QMap commands READ getScriptCommands WRITE setScriptCommands REQUIRED)
    QMap<QString, QVariant> _commands;

    static const char *defaultConnection;

    bool setDatabaseConnection(const QSqlDatabase &dbDatabase);
    QVariant buildResponseVariant(QSharedPointer<EventContext> apiResponse);

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

    BotScript &operator=(const BotScript &other);

    BotScript() {}
    ~BotScript() {}
    BotScript(const BotScript &other);

    bool invokable() override;

    QMap<QString, QVariant> getScriptCommands() const;
    QString getScriptName() const;
    QString findCommandMapping(const QString &command) const;

    void execute(const QByteArray &command, const EventContext &message) override;
    void initAPI(const QString &botToken);
    void postResult(const Message &message);
    void setScriptCommands(QMap<QString, QVariant> commands);
    void setScriptName(const QString &name);

public slots:

    /*
     *  QSqlDatabase
     */
    bool dbOpen();
    bool dbOpen(const QString& user, const QString& dbPassword);
    void dbClose();
    bool dbIsOpen() const;
    bool dbIsOpenError() const;
    QStringList dbTables(TableType type = Tables) const;
    QString dbLastDatabaseError() const;
    bool dbIsDatabaseValid() const;
    bool dbTransaction();
    bool dbCommit();
    bool dbRollback();
    void setDatabaseConnection(const QString &name);
    void dbSetDatabaseName(const QString &name);
    void dbSetUserName(const QString &name);
    void dbSetPassword(const QString &dbPassword);
    void dbSetHostName(const QString &host);
    void dbSetPort(int p);
    void dbSetConnectOptions(const QString &options = QString());
    QString dbDatabaseName() const;
    QString dbUserName() const;
    QString dbPassword() const;
    QString dbHostName() const;
    QString dbDriverName() const;
    int dbPort() const;
    QString dbCconnectOptions() const;
    QString dbConnectionName() const;
    void dbSetNumericalPrecisionPolicy(NumericalPrecisionPolicy precisionPolicy);
    NumericalPrecisionPolicy dbNumericalPrecisionPolicy() const;
    bool dbAddDatabase(const QString &type, const QString &dbConnectionName = QLatin1String(defaultConnection));
    bool dbDatabase(const QString& dbConnectionName = QLatin1String(defaultConnection), bool dbOpen = true);
    void dbRemoveDatabase(const QString& dbConnectionName);
    bool dbContains(const QString& dbConnectionName = QLatin1String(defaultConnection));
    QStringList dbDrivers();
    QStringList dbConnectionNames();
    bool dbIsDriverAvailable(const QString &name);

    /*
     *  QSqlQuery
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
     *  DiscordAPI
     */

    // Channel API functions.
    // https://discord.com/developers/docs/resources/channel

    QVariant cCreateMessage(QVariant contextVariant);
};

Q_DECLARE_METATYPE(BotScript)

#endif // BOTSCRIPT_H
