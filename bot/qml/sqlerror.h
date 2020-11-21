/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
