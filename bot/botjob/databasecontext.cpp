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

#include "databasecontext.h"

#include "util/globals.h"
#include "util/enumutils.h"

DatabaseContext::DatabaseContext(QSharedPointer<Settings> settings) {
    hostName = settings->value(SettingsParam::Database::DATABASE_HOST).toString();

    port = settings->value(SettingsParam::Database::DATABASE_PORT).toInt();

    userName = settings->value(SettingsParam::Database::DATABASE_USER).toString();

    password = settings->value(SettingsParam::Database::DATABASE_PASSWORD).toString();

    driverName = settings->value(SettingsParam::Database::DATABASE_TYPE).toString();

    databaseName = settings->value(SettingsParam::Database::DATABASE_NAME).toString();

    type = EnumUtils::keyToValue<SettingsParam::Database::DatabaseType>(driverName);

    minPoolSize = settings->value(SettingsParam::Database::MIN_POOL_SIZE).toInt();

    maxPoolSize = settings->value(SettingsParam::Database::MAX_POOL_SIZE).toInt();
}

DatabaseContext::DatabaseContext(const DatabaseContext &other) {
    hostName = other.hostName;

    port = other.port;

    userName = other.userName;

    password = other.password;

    driverName = other.driverName;

    type = other.type;

    guildId = other.guildId;

    scriptName = other.scriptName;

    databaseName = other.databaseName;

    _connectionName = other._connectionName;

    minPoolSize = other.minPoolSize;

    maxPoolSize = other.maxPoolSize;
}

DatabaseContext&
DatabaseContext::operator=(const DatabaseContext &other) {
    hostName = other.hostName;

    port = other.port;

    userName = other.userName;

    password = other.password;

    driverName = other.driverName;

    type = other.type;

    guildId = other.guildId;

    scriptName = other.scriptName;

    databaseName = other.databaseName;

    minPoolSize = other.minPoolSize;

    maxPoolSize = other.maxPoolSize;

    return *this;
}

void
DatabaseContext::setConnectionName(const QString &scriptName, const QString &guildId) {
    _connectionName = QString("%1|%2|%3")
            .arg(scriptName)
            .arg(guildId)
            .arg(type);
}

QString
DatabaseContext::getConnectionName() const {
    return _connectionName;
}
