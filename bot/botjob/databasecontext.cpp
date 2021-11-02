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

#include "util/databasetype.h"
#include "util/enumutils.h"


void
DatabaseContext::init() {
    hostName = Settings::databaseHost();

    port = Settings::databasePort();

    userName = Settings::databaseUser();

    password = Settings::databasePassword();

    driverName = Settings::databaseType();

    databaseName = Settings::databaseName();

    type = EnumUtils::keyToValue<DatabaseType::Type>(driverName);

    maxPoolSize = Settings::maxPoolSize();
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
    if (this == &other) {
        return *this;
    }

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

QString
DatabaseContext::getConnectionName() const {
    return QString("%1|%2|%3")
            .arg(scriptName)
            .arg(guildId)
            .arg(type);
}
