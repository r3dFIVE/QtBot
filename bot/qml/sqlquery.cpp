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

#include "sqlquery.h"

#include <QSql>


SqlQuery::SqlQuery(const SqlQuery &other, QObject *parent) : QObject(parent) {
    if (this == &other) {
        return;
    }

    _query = other._query;
}


SqlQuery::SqlQuery(SqlDatabase *database, const QString &query, QObject *parent) : QObject(parent) {
    _query = QSqlQuery(query, database->sqlDatabase());


}

SqlQuery::SqlQuery(const QSqlQuery &other, QObject *parent) : QObject(parent) {
    _query = other;
}

SqlQuery
&SqlQuery::operator=(const SqlQuery &other) {
    if (this == &other) {
        return *this;
    }

    _query = other._query;

    return *this;
}

bool
SqlQuery::isValid() const {
    return _query.isValid();
}

bool
SqlQuery::isActive() const{
    return _query.isActive();
}

bool
SqlQuery::isNull(int field) const {
    return _query.isNull(field);
}

bool
SqlQuery::isNull(const QString &name) const {
    return _query.isNull(name);
}

int
SqlQuery::at() const {
    return _query.at();
}

QString
SqlQuery::lastErrorText() const {
    return _query.lastError().text();
}

QString
SqlQuery::lastQuery() const {
    return _query.lastQuery();
}

int
SqlQuery::numRowsAffected() const {
    return _query.numRowsAffected();
}

SqlError*
SqlQuery::lastError() const {
    return new SqlError(_query.lastError());
}

bool
SqlQuery::isSelect() const {
    return _query.isSelect();
}

int SqlQuery::size() const {
    return _query.size();
}

bool
SqlQuery::isForwardOnly() const {
    return _query.isForwardOnly();
}


void
SqlQuery::setForwardOnly(bool forward) {
    _query.setForwardOnly(forward);
}

QVariant
SqlQuery::value(int i) const {
    return _query.value(i);
}

QVariant
SqlQuery::value(const QString &name) const {
    return _query.value(name);
}

void
SqlQuery::setNumericalPrecisionPolicy(Sql::NumericalPrecisionPolicy precisionPolicy) {
    _query.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
}

Sql::NumericalPrecisionPolicy
SqlQuery::numericalPrecisionPolicy() const {
    return Sql::NumericalPrecisionPolicy(_query.numericalPrecisionPolicy());
}

bool
SqlQuery::seek(int i, bool relative) {
    return _query.seek(i, relative);
}

bool
SqlQuery::next() {
    return _query.next();
}

bool
SqlQuery::previous() {
    return _query.previous();
}

bool
SqlQuery::first() {
    return _query.first();
}

bool
SqlQuery::last() {
    return _query.last();
}

void
SqlQuery::clear() {
    _query.clear();
}

bool
SqlQuery::prepare(const QString &query) {
    return _query.prepare(query);
}

bool
SqlQuery::exec() {
    return _query.exec();
}

bool
SqlQuery::execBatch(Sql::BatchExecutionMode mode) {
    return _query.execBatch(QSqlQuery::BatchExecutionMode(mode));
}

bool
SqlQuery::exec(const QString &query) {
    return _query.exec(query);
}

void
SqlQuery::bindValue(const QString &placeholder, const QVariant &value, Sql::ParamTypeFlag type) {
    _query.bindValue(placeholder, value, QSql::ParamTypeFlag(type));
}

void
SqlQuery::bindValue(int pos, const QVariant &value, Sql::ParamTypeFlag type) {
    _query.bindValue(pos, value, QSql::ParamTypeFlag(type));
}

void
SqlQuery::addBindValue(const QVariant &val, Sql::ParamTypeFlag type) {
    _query.addBindValue(val, QSql::ParamTypeFlag(type));
}

QVariant
SqlQuery::boundValue(const QString &placeholder) const {
    return _query.boundValue(placeholder);
}

QVariant
SqlQuery::boundValue(int pos) const {
    return _query.boundValue(pos);
}

QMap<QString, QVariant>
SqlQuery::boundValues() const {
    return _query.boundValues();
}

QString
SqlQuery::executedQuery() const {
    return _query.executedQuery();
}

QVariant
SqlQuery::lastInsertId() const {
    return _query.lastInsertId();
}

void
SqlQuery::finish() {
    return _query.finish();
}

bool
SqlQuery::nextResult() {
    return _query.nextResult();
}
