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

#ifndef DATABASECONTEXT_H
#define DATABASECONTEXT_H

#include <QSharedPointer>

#include "util/settings.h"


class DatabaseContext
{       
    QString _connectionName;

public:
    int minPoolSize;
    int maxPoolSize;
    int port;
    int type;
    QString hostName;
    QString userName;
    QString password;
    QString databaseName;
    QString driverName;
    QString scriptName;
    QString guildId;

    DatabaseContext() {}
    DatabaseContext(QSharedPointer<Settings> settings);
    DatabaseContext(const DatabaseContext &other);
    ~DatabaseContext() {}

    DatabaseContext& operator=(const DatabaseContext &other);

    void setConnectionName(const QString &scriptName, const QString &guildId);
    QString getConnectionName() const;

};

#endif // DATABASECONTEXT_H
