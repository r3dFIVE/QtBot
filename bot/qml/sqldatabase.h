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

#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include <QList>
#include <QMap>
#include <QMutex>
#include <QObject>
#include <QSqlDatabase>
#include <QMutexLocker>

#include "entity/idbmanager.h"
#include "botjob/databasecontext.h"
#include "sqlerror.h"
#include "enums/sql.h"
#include "util/enumutils.h"
#include "util/databasetype.h"
#include "logging/logfactory.h"


class SqlDatabase : public QObject
{
    Q_OBJECT

    Logger *_logger = LogFactory::getLogger(this);

    int _port = 0;
    int _type = 0;
    QString _connectionNameBase;
    QString _connectionName;
    QString _databaseName;
    QString _driverName = EnumUtils::valueToKey(DatabaseType::QMYSQL);
    QString _hostName;
    QString _password;
    QString _userName;
    QSqlDatabase _database;

    void setConnectionName();

public:
    SqlDatabase(QObject *parent = nullptr) : QObject(parent) {}
    SqlDatabase(const SqlDatabase &other, QObject *parent = nullptr);
    SqlDatabase(const DatabaseContext &context, QObject *parent = nullptr);
    ~SqlDatabase() {
       _database = QSqlDatabase();

       QSqlDatabase::removeDatabase(_connectionName);

       QString ptrStr = QString("0x%1").arg((quintptr)this,
                           QT_POINTER_SIZE * 2, 16, QChar('0'));

       _logger->trace(QString("Destroyed SqlDatabase(%1)").arg(ptrStr));
    }

    Q_INVOKABLE SqlDatabase &operator=(const SqlDatabase &other);

    Q_INVOKABLE bool open(QString connectionName = QString("%1").arg(QDateTime::currentMSecsSinceEpoch()));
    Q_INVOKABLE void close();
    Q_INVOKABLE bool isOpen() const;
    Q_INVOKABLE bool isOpenError() const;
    Q_INVOKABLE QStringList dbTables(Sql::TableType type = Sql::Tables) const;
    Q_INVOKABLE SqlError lastError() const;
    Q_INVOKABLE bool isDatabaseValid() const;
    Q_INVOKABLE bool transaction();
    Q_INVOKABLE bool commit();
    Q_INVOKABLE bool rollback();
    Q_INVOKABLE void setDatabaseName(const QString &name);
    Q_INVOKABLE void setUserName(const QString &name);
    Q_INVOKABLE void setPassword(const QString &dbPassword);
    Q_INVOKABLE void setHostName(const QString &host);
    Q_INVOKABLE void setPort(int p);
    Q_INVOKABLE void setConnectOptions(const QString &options = QString());
    Q_INVOKABLE QString databaseName() const;
    Q_INVOKABLE QString userName() const;
    Q_INVOKABLE QString hostName() const;
    Q_INVOKABLE QString driverName() const;
    Q_INVOKABLE QSqlDatabase sqlDatabase();
    Q_INVOKABLE int port() const;
    Q_INVOKABLE QString connectOptions() const;
    Q_INVOKABLE void setNumericalPrecisionPolicy(const Sql::NumericalPrecisionPolicy &precisionPolicy);
    Q_INVOKABLE Sql::NumericalPrecisionPolicy numericalPrecisionPolicy() const;
    Q_INVOKABLE void setType(const QString &type);
    Q_INVOKABLE QStringList drivers() const;
    Q_INVOKABLE bool isDriverAvailable(const QString &name);
};

Q_DECLARE_METATYPE(SqlDatabase)

#endif // SQL_DATABASE_H
