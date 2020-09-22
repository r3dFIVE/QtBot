#include "sqlerror.h"

SqlError::SqlError(const QString &driverText, const QString &databaseText, Sql::ErrorType type, const QString &errorCode) {
    _sqlError = QSqlError(driverText, databaseText, QSqlError::ErrorType(type), errorCode);
}

SqlError::SqlError(const SqlError &other) {
    _sqlError = other._sqlError;
}

SqlError::SqlError(SqlError *other) {
    _sqlError = other->_sqlError;
}

SqlError::SqlError(const QSqlError &other) {
    _sqlError = other;
}

SqlError
&SqlError::operator=(const SqlError &other) {
    _sqlError = other._sqlError;

    return *this;
}

QString
SqlError::driverText() const {
    return _sqlError.driverText();
}

QString
SqlError::databaseText() const {
    return _sqlError.databaseText();
}

Sql::ErrorType
SqlError::type() const {
    return Sql::ErrorType(_sqlError.type());
}

QString
SqlError::nativeErrorCode() const {
    return _sqlError.nativeErrorCode();
}

QString
SqlError::text() const {
    return _sqlError.text();
}

bool
SqlError::isValid() const {
    return _sqlError.isValid();
}
