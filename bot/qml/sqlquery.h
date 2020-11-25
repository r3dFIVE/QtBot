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

#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QObject>
#include <QSqlQuery>
#include <QVariant>

#include "enums/sql.h"
#include "sqldatabase.h"
#include "sqlerror.h"
#include "sqlrecord.h"

class SqlDatabase;

class SqlQuery : public QObject
{
    Q_OBJECT

    QSqlQuery _query;
    SqlDatabase *_database;

public:
    Q_INVOKABLE SqlQuery() {}
    Q_INVOKABLE SqlQuery(const SqlQuery &other);
    Q_INVOKABLE SqlQuery(SqlQuery *other);
    Q_INVOKABLE SqlQuery(const QSqlQuery &other);
    Q_INVOKABLE ~SqlQuery() {}
    Q_INVOKABLE SqlQuery(SqlDatabase *database, const QString &query = QString());
    Q_INVOKABLE SqlQuery& operator=(const SqlQuery& other);
    Q_INVOKABLE bool isValid() const;
    Q_INVOKABLE bool isActive() const;
    Q_INVOKABLE bool isNull(int field) const;
    Q_INVOKABLE bool isNull(const QString &name) const;
    Q_INVOKABLE int at() const;
    Q_INVOKABLE QString lastErrorText() const;
    Q_INVOKABLE QString lastQuery() const;
    Q_INVOKABLE int numRowsAffected() const;
    Q_INVOKABLE QVariant lastError() const;
    Q_INVOKABLE bool isSelect() const;
    Q_INVOKABLE int size() const;
    Q_INVOKABLE bool isForwardOnly() const;
    Q_INVOKABLE SqlRecord record() const;
    Q_INVOKABLE void setForwardOnly(bool forward);
    Q_INVOKABLE bool exec(const QString& query);
    Q_INVOKABLE QVariant value(int i) const;
    Q_INVOKABLE QVariant value(const QString& name) const;
    Q_INVOKABLE void setNumericalPrecisionPolicy(Sql::NumericalPrecisionPolicy precisionPolicy);
    Q_INVOKABLE Sql::NumericalPrecisionPolicy numericalPrecisionPolicy() const;
    Q_INVOKABLE bool seek(int i, bool relative = false);
    Q_INVOKABLE bool next();
    Q_INVOKABLE bool previous();
    Q_INVOKABLE bool first();
    Q_INVOKABLE bool last();
    Q_INVOKABLE void clear();
    Q_INVOKABLE bool exec();
    Q_INVOKABLE bool execBatch(Sql::BatchExecutionMode mode = Sql::ValuesAsRows);
    Q_INVOKABLE bool prepare(const QString& query);
    Q_INVOKABLE void bindValue(const QString& placeholder, const QVariant& val,
                   Sql::ParamTypeFlag type = Sql::In);
    Q_INVOKABLE void bindValue(int pos, const QVariant& val, Sql::ParamTypeFlag type = Sql::In);
    Q_INVOKABLE void addBindValue(const QVariant& val, Sql::ParamTypeFlag type = Sql::In);
    Q_INVOKABLE QVariant boundValue(const QString& placeholder) const;
    Q_INVOKABLE QVariant boundValue(int pos) const;
    Q_INVOKABLE QMap<QString, QVariant> boundValues() const;
    Q_INVOKABLE QString executedQuery() const;
    Q_INVOKABLE QVariant lastInsertId() const;
    Q_INVOKABLE void finish();
    Q_INVOKABLE bool nextResult();
    Q_INVOKABLE SqlDatabase *getDatabase();
};

Q_DECLARE_METATYPE(SqlQuery)

#endif // SQLQUERY_H
