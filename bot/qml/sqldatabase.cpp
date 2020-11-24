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

#include "sqldatabase.h"

#include <QSqlError>

#include "util/globals.h"
#include "util/enumutils.h"

QMutex SqlDatabase::_mutex;
QMap<QString, QList<SqlQuery *> > SqlDatabase::_queries;

SqlDatabase::SqlDatabase(const SqlDatabase &other) {
    _database = other._database;

    _defaultDatabaseContext = other._defaultDatabaseContext;

    _hostName = other._hostName;

    _userName = other._userName;

    _password = other._password;

    _databaseName = other._databaseName;

    _port = other._port;

    _type = other._type;

    _connectionName = other._connectionName;
}

SqlDatabase::SqlDatabase(const DatabaseContext &databaseContext) {
    _defaultDatabaseContext = databaseContext;
}

SqlDatabase
&SqlDatabase::operator=(const SqlDatabase &other) {
    _database = other._database;

    _defaultDatabaseContext = other._defaultDatabaseContext;

    _hostName = other._hostName;

    _userName = other._userName;

    _password = other._password;

    _databaseName = other._databaseName;

    _port = other._port;

    _type = other._type;

    _connectionName = other._connectionName;

    return *this;
}

bool
SqlDatabase::open(QString suffix) {
    _connectionName = QString ("%1|%2")
            .arg(_defaultDatabaseContext.getConnectionName())
            .arg(suffix);

    closeExistingConnection(_connectionName);

    _database = QSqlDatabase::addDatabase(_defaultDatabaseContext.driverName, _connectionName);

    if (_hostName.isEmpty()) {
        _hostName = _defaultDatabaseContext.hostName;

        _database.setHostName(_hostName);
    }


    if (_userName.isEmpty()) {
        _userName = _defaultDatabaseContext.userName;

        _database.setUserName(_userName);
    }

    if (_password.isEmpty()) {
        _password = _defaultDatabaseContext.password;

        _database.setPassword(_password);
    }

    if (_port == 0) {
        _port = _defaultDatabaseContext.port;

        _database.setPort(_port);
    }

    if (_databaseName.isEmpty()) {
        _databaseName = _defaultDatabaseContext.databaseName;

        _database.setDatabaseName(_databaseName);
    }

    return _database.open();
}

void
SqlDatabase::closeExistingConnection(QString existingConnection) {
    if (QSqlDatabase::contains(existingConnection)) {
        for (auto query : getQueriesForConnection(existingConnection)) {
            if (query) {
                SqlDatabase *db = query->getDatabase();

                if (db && db->isOpen()) {
                    db->close();
                }
            }
        }

        _queries[existingConnection].clear();

        QSqlDatabase::removeDatabase(existingConnection);
    }
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
    _defaultDatabaseContext.databaseName = databaseName;
}

void
SqlDatabase::setUserName(const QString &userName) {
    _defaultDatabaseContext.userName = userName;
}

void
SqlDatabase::setPassword(const QString &password) {
    _defaultDatabaseContext.password = password;
}


void
SqlDatabase::setHostName(const QString &hostName) {
    _defaultDatabaseContext.hostName = hostName;
}

void
SqlDatabase::setPort(int port) {
    _defaultDatabaseContext.port = port;
}

void
SqlDatabase::setConnectOptions(const QString &options) {
    _database.setConnectOptions(options);
}

QString
SqlDatabase::databaseName() const {
    return _defaultDatabaseContext.databaseName;
}

QString
SqlDatabase::userName() const {
    return _defaultDatabaseContext.userName;
}

QString
SqlDatabase::hostName() const {
    return _defaultDatabaseContext.hostName;
}

QString
SqlDatabase::driverName() const {
    return _defaultDatabaseContext.driverName;
}

int
SqlDatabase::port() const {
    return _defaultDatabaseContext.port;
}

QString
SqlDatabase::connectOptions() const {
    return _database.connectOptions();
}

QString
SqlDatabase::connectionName() const {
    return _defaultDatabaseContext.getConnectionName();
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
    _defaultDatabaseContext.type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(type);
}

QStringList
SqlDatabase::drivers() {
    return QSqlDatabase::drivers();
}

bool
SqlDatabase::isDriverAvailable(const QString &name) {
    return QSqlDatabase::isDriverAvailable(name);
}

void
SqlDatabase::addQuery(SqlQuery *query) {
    _mutex.lock();

    _queries[_connectionName] << query;

    _mutex.unlock();
}

void
SqlDatabase::setConnectionName() {
    _defaultDatabaseContext.setConnectionName(_defaultDatabaseContext.scriptName, _defaultDatabaseContext.guildId);
}

QList<SqlQuery *>
SqlDatabase::getQueriesForConnection(const QString &existingConnection) {
    _mutex.lock();

    QList<SqlQuery *> queries = _queries[existingConnection];

    _mutex.unlock();

    return queries;
}

void
SqlDatabase::clearQueries() {
    _queries.clear();
}


void
SqlDatabase::setConnectionName(const QString &scriptName, const QString &guildId) {
    _defaultDatabaseContext.setConnectionName(scriptName, guildId);
}

QSqlDatabase
SqlDatabase::sqlDatabase() {
    return _database;
}
