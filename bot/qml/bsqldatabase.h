#ifndef BSQLDATABASE_H
#define BSQLDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class BSqlDatabase : public QObject
{
    Q_OBJECT

    QSqlDatabase _database;
    QSqlQuery _query;

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

    Q_INVOKABLE BSqlDatabase() {}
    Q_INVOKABLE BSqlDatabase(const BSqlDatabase &other);
    Q_INVOKABLE ~BSqlDatabase() {}

    Q_INVOKABLE BSqlDatabase &operator=(const BSqlDatabase &other);

    static const char *defaultConnection;

    bool setDatabaseConnection(const QSqlDatabase &database);

public slots:
    bool open();
    bool open(const QString& user, const QString& password);
    void close();
    bool isOpen() const;
    bool isOpenError() const;
    QStringList tables(TableType type = Tables) const;

    QString lastDatabaseError() const;
    bool isDatabaseValid() const;

    bool transaction();
    bool commit();
    bool rollback();

    void setDatabaseConnection(const QString &name);
    void setDatabaseName(const QString &name);
    void setUserName(const QString &name);
    void setPassword(const QString &password);
    void setHostName(const QString &host);
    void setPort(int p);
    void setConnectOptions(const QString &options = QString());

    /* QSqlDatabase */
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    QString driverName() const;
    int port() const;
    QString connectOptions() const;
    QString connectionName() const;
    void setNumericalPrecisionPolicy(NumericalPrecisionPolicy precisionPolicy);
    NumericalPrecisionPolicy numericalPrecisionPolicy() const;
    bool addDatabase(const QString &type, const QString &connectionName = QLatin1String(defaultConnection));
    bool database(const QString& connectionName = QLatin1String(defaultConnection), bool open = true);
    void removeDatabase(const QString& connectionName);
    bool contains(const QString& connectionName = QLatin1String(defaultConnection));
    QStringList drivers();
    QStringList connectionNames();
    bool isDriverAvailable(const QString &name);


    /* QSqlQuery */
    QVariant value(int i) const;
    QVariant value(const QString& name) const;
    bool seek(int i, bool relative = false);
    bool next();
    bool prepare(const QString &query);
    bool exec();
    bool exec(const QString &query);

    void bindValue(const QString& placeholder, const QVariant& val,
                   QSql::ParamType type = QSql::In);
    void bindValue(int pos, const QVariant& val, QSql::ParamType type = QSql::In);

};

Q_DECLARE_METATYPE(BSqlDatabase)

#endif // BSQLDATABASE_H
