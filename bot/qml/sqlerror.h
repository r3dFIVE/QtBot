#ifndef SQLERROR_H
#define SQLERROR_H

#include <QObject>
#include <QSqlError>

#include "enums/sql.h"

class SqlError : public QObject
{
    Q_OBJECT

    QSqlError _sqlError;

public:
    SqlError(const QString &driverText = QString(),
              const QString &databaseText = QString(),
              Sql::ErrorType type = Sql::NoError,
              const QString &errorCode = QString());
    SqlError(const SqlError &other);
    SqlError(SqlError *other);
    SqlError(const QSqlError &other);
    ~SqlError() {}

    SqlError& operator=(const SqlError& other);
    SqlError &operator=(SqlError &&other) noexcept { _sqlError.swap(other._sqlError); return *this; }

    bool operator==(const SqlError& other) const;
    bool operator!=(const SqlError& other) const;

    QString driverText() const;
    QString databaseText() const;
    Sql::ErrorType type() const;

    QString nativeErrorCode() const;
    QString text() const;
    bool isValid() const;
};

Q_DECLARE_METATYPE(SqlError)

#endif // SQLERROR_H
