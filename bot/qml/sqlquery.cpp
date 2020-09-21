#include "sqlquery.h"

SqlQuery::SqlQuery(const SqlQuery &other) {
    _database = other._database;

    _query = other._query;
}

SqlQuery::SqlQuery(const SqlDatabase &database) {
    SqlDatabase _database = database;

    _query = QSqlQuery(_database.getDatabase());
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
SqlQuery::qryIsNull(int field) const {
    return _query.isNull(field);
}

bool SqlQuery::qryIsNull(const QString &name) const {
    return _query.isNull(name);
}

int
SqlQuery::qryAt() const {
    return _query.at();
}

QString
SqlQuery::qryLastQuery() const {
    return _query.lastQuery();
}

int
SqlQuery::qryNumRowsAffected() const {
    return _query.numRowsAffected();
}

//QString
//SqlQuery::qryLastError() const {
//    return _query.lastError().text();
//}

bool
SqlQuery::qryIsSelect() const {
    return _query.isSelect();
}

int SqlQuery::qrySize() const {
    return _query.size();
}

bool
SqlQuery::qryIsForwardOnly() const {
    return _query.isForwardOnly();
}

void
SqlQuery::qrySetForwardOnly(bool forward) {
    _query.setForwardOnly(forward);
}

//QVariant
//SqlQuery::qryValue(int i) const {
//    return _query.value(i);
//}

//QVariant
//SqlQuery::qryValue(const QString &name) const {
//    return _query.value(name);
//}

//void
//SqlQuery::qrySetNumericalPrecisionPolicy(SqlQuery::NumericalPrecisionPolicy precisionPolicy) {
//    _query.setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy(precisionPolicy));
//}

//SqlQuery::NumericalPrecisionPolicy
//SqlQuery::qryNumericalPrecisionPolicy() const {
//    return SqlQuery::NumericalPrecisionPolicy(_query.numericalPrecisionPolicy());
//}

bool
SqlQuery::qrySeek(int i, bool relative) {
    return _query.seek(i, relative);
}

bool
SqlQuery::qryNext() {
    return _query.next();
}

bool
SqlQuery::qryPrevious() {
    return _query.previous();
}

bool
SqlQuery::qryFirst() {
    return _query.first();
}

bool
SqlQuery::qryLast() {
    return _query.last();
}

void
SqlQuery::qryClear() {
    _query.clear();
}

bool
SqlQuery::qryPrepare(const QString &query) {
    return _query.prepare(query);
}

bool
SqlQuery::qryExec() {
    return _query.exec();
}

//bool
//SqlQuery::execBatch(SqlQuery::BatchExecutionMode mode) {
//    return _query.execBatch(QSqlQuery::BatchExecutionMode(mode));
//}

bool
SqlQuery::qryExec(const QString &query) {
    return _query.exec(query);
}

//void
//SqlQuery::qryBindValue(const QString &placeholder, const QVariant &value, ParamType type) {
//    _query.bindValue(placeholder, value, QSql::ParamType(type));
//}

//void
//SqlQuery::qryBindValue(int pos, const QVariant &value, ParamType type) {
//    _query.bindValue(pos, value, QSql::ParamType(type));
//}

//void
//SqlQuery::qryAddBindValue(const QVariant &val, ParamType type) {
//    _query.addBindValue(val, QSql::ParamType(type));
//}

QVariant
SqlQuery::qryBoundValue(const QString &placeholder) const {
    return _query.boundValue(placeholder);
}

QVariant
SqlQuery::qryBoundValue(int pos) const {
    return _query.boundValue(pos);
}

QMap<QString, QVariant>
SqlQuery::boundValues() const {
    return _query.boundValues();
}

QString
SqlQuery::qryExecutedQuery() const {
    return _query.executedQuery();
}

QVariant SqlQuery::qryLastInsertId() const {
    return _query.lastInsertId();
}

void
SqlQuery::qryFinish() {
    return _query.finish();
}

bool
SqlQuery::qryNextResult() {
    return _query.nextResult();
}
