/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
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
    static const QString TYPE_NAME;

    Q_INVOKABLE SqlError() {}
    Q_INVOKABLE SqlError(const SqlError &other);
    Q_INVOKABLE SqlError(SqlError *other);
    Q_INVOKABLE SqlError(const QSqlError &other);
    Q_INVOKABLE ~SqlError() {}

    Q_INVOKABLE SqlError &operator=(const SqlError &other);
    Q_INVOKABLE SqlError &operator=(SqlError &&other) noexcept;

    Q_INVOKABLE bool operator==(const SqlError& other) const;
    Q_INVOKABLE bool operator!=(const SqlError& other) const;

    Q_INVOKABLE QString driverText() const;
    Q_INVOKABLE QString databaseText() const;
    Q_INVOKABLE Sql::ErrorType type() const;

    Q_INVOKABLE QString nativeErrorCode() const;
    Q_INVOKABLE QString text() const;
    Q_INVOKABLE bool isValid() const;
};

Q_DECLARE_METATYPE(SqlError)

#endif // SQLERROR_H
