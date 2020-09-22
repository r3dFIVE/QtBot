#include "sqlquery.h"

#include <QSql>


SqlQuery::SqlQuery(const SqlQuery &other) {
    _database = other._database;

    _query = other._query;
}

SqlQuery::SqlQuery(SqlQuery *other) {
    _database = other->_database;

    _query = other->_query;
}

SqlQuery::SqlQuery(SqlDatabase *database, const QString &query) {
    _database = database;

    _query = QSqlQuery(query, _database->sqlDatabase());

    _database->addQuery(this);
}

SqlQuery::SqlQuery(const QSqlQuery &other) {
    _query = other;
}

SqlQuery
&SqlQuery::operator=(const SqlQuery &other) {
    _database = other._database;

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
SqlQuery::lastQuery() const {
    return _query.lastQuery();
}

int
SqlQuery::numRowsAffected() const {
    return _query.numRowsAffected();
}

SqlError
SqlQuery::lastError() const {
    return SqlError(_query.lastError());
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

SqlRecord
SqlQuery::record() const {
    return SqlRecord(_query.record());
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

SqlDatabase*
SqlQuery::getDatabase() {
    return _database;
}
