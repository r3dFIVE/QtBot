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

#include "sqlerror.h"
#include <QDebug>

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
