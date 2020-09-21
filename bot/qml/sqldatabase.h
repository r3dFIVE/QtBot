#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include "botjob/databasecontext.h"

class SqlDatabase : public QObject
{
    Q_OBJECT

    DatabaseContext _databaseContext;
    QSqlDatabase _database;

    void closeExistingConnection();
    void setConnectionName();
public:
    SqlDatabase() {}
    SqlDatabase(const SqlDatabase &other);
    SqlDatabase(const DatabaseContext &context);
    ~SqlDatabase() {
        _database.close();
    }

    SqlDatabase &operator=(const SqlDatabase &other);

    void setConnectionName(const QString &scriptName, const QString &getGuildId);

    QSqlDatabase getDatabase();

public slots:
    bool dbOpen();
    void dbClose();
    bool dbIsOpen() const;
    bool dbIsOpenError() const;
    //QStringList dbTables(TableType type = Tables) const;
   // QString dbLastDatabaseError() const;
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
    //void dbSetNumericalPrecisionPolicy(const NumericalPrecisionPolicy &precisionPolicy);
    //NumericalPrecisionPolicy dbNumericalPrecisionPolicy() const;
    //void dbSetType(const QString &type);
    QStringList dbDrivers();
    bool dbIsDriverAvailable(const QString &name);


};

Q_DECLARE_METATYPE(SqlDatabase)

#endif // SQL_DATABASE_H
