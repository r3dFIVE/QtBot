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

#include "sqldatabase.h"

#include <QSqlError>



SqlDatabase::SqlDatabase(const SqlDatabase &other, QObject *parent) : QObject(parent) {
    _database = other._database;

    _hostName = other._hostName;

    _userName = other._userName;

    _password = other._password;

    _databaseName = other._databaseName;

    _driverName = other._driverName;

    _port = other._port;

    _type = other._type;

    _connectionNameBase = other._connectionNameBase;
}

SqlDatabase::SqlDatabase(const DatabaseContext &databaseContext, QObject *parent) : QObject(parent) {
    _userName = databaseContext.userName;

    _password = databaseContext.password;

    _databaseName = databaseContext.databaseName;

    _port = databaseContext.port;

    _type = databaseContext.type;

    _connectionNameBase = databaseContext.getConnectionName();
}

SqlDatabase
&SqlDatabase::operator=(const SqlDatabase &other) {
    if (this == &other) {
        return *this;
    }

    _database = other._database;

    _hostName = other._hostName;

    _userName = other._userName;

    _password = other._password;

    _databaseName = other._databaseName;

    _port = other._port;

    _type = other._type;

    _connectionNameBase = other._connectionNameBase;

    return *this;
}

bool
SqlDatabase::open(QString suffix) {
    _connectionName = QString ("%1|%2")
            .arg(_connectionNameBase)
            .arg(suffix);

    _database = QSqlDatabase::addDatabase(_driverName, _connectionName);

    if (_hostName.isEmpty()) {
        _logger->warning("SQL Connection failed... Must provide a valid host name.");

        return false;
    } else {
        _database.setHostName(_hostName);
    }

    if (_userName.isEmpty()) {
        _logger->warning("SQL Connection failed... Must provide a user name.");

        return false;
    } else {
        _database.setUserName(_userName);
    }

    if (_password.isEmpty()) {
        _logger->warning("SQL Connection failed... Must provide a password.");

        return false;
    } else {
        _database.setPassword(_password);
    }

    if (_port == 0) {
        _logger->warning("SQL Connection failed... Must provide a valid port.");

        return false;
    } else {
        _database.setPort(_port);
    }

    if (_databaseName.isEmpty()) {
        _logger->warning("SQL Connection failed... Must provide a database name.");

        return false;
    } else {
        _database.setDatabaseName(_databaseName);
    }

    return _database.open();
}

void
SqlDatabase::close() {
    _database.close();

    _database = QSqlDatabase();
}

bool
SqlDatabase::isOpen() const {
    if (_database.isValid()) {
        return _database.isOpen();
    }

    return false;
}

bool
SqlDatabase::isOpenError() const {
    return _database.isOpenError();
}

QStringList
SqlDatabase::dbTables(Sql::TableType type) const {
    return _database.tables(QSql::TableType(type));
}

SqlError
SqlDatabase::lastError() const {
    return SqlError(_database.lastError());
}


bool
SqlDatabase::isDatabaseValid() const {
    return _database.isValid();
}

bool
SqlDatabase::transaction() {
    return _database.transaction();
}

bool
SqlDatabase::commit() {
    return _database.commit();
}

bool
SqlDatabase::rollback() {
    return _database.rollback();
}

void
SqlDatabase::setDatabaseName(const QString &databaseName) {
    _databaseName = databaseName;
}

void
SqlDatabase::setUserName(const QString &userName) {
    _userName = userName;
}

void
SqlDatabase::setPassword(const QString &password) {
    _password = password;
}


void
SqlDatabase::setHostName(const QString &hostName) {
    _hostName = hostName;
}

void
SqlDatabase::setPort(int port) {
    _port = port;
}

void
SqlDatabase::setConnectOptions(const QString &options) {
    _database.setConnectOptions(options);
}

QString
SqlDatabase::databaseName() const {
    return _databaseName;
}

QString
SqlDatabase::userName() const {
    return _userName;
}

QString
SqlDatabase::hostName() const {
    return _hostName;
}

QString
SqlDatabase::driverName() const {
    return _driverName;
}

int
SqlDatabase::port() const {
    return _port;
}

QString
SqlDatabase::connectOptions() const {
    return _database.connectOptions();
}

void
SqlDatabase::setNumericalPrecisionPolicy(const Sql::NumericalPrecisionPolicy &precisionPolicy) {
    _database.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
}

Sql::NumericalPrecisionPolicy
SqlDatabase::numericalPrecisionPolicy() const {
    return Sql::NumericalPrecisionPolicy(_database.numericalPrecisionPolicy());
}

void
SqlDatabase::setType(const QString &type) {
    _type = EnumUtils::keyToValue<DatabaseType::Type>(type);
}

QStringList
SqlDatabase::drivers() const {
    return QSqlDatabase::drivers();
}

bool
SqlDatabase::isDriverAvailable(const QString &name) {
    return QSqlDatabase::isDriverAvailable(name);
}

QSqlDatabase
SqlDatabase::sqlDatabase() {
    return _database;
}
