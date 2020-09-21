#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QObject>
#include <QSqlQuery>
#include <QVariant>

#include "sqldatabase.h"


class SqlQuery : public QObject
{
    Q_OBJECT

    QSqlQuery _query;
    SqlDatabase _database;

public:
    SqlQuery() {}
    SqlQuery(const SqlQuery &other);
    SqlQuery(const SqlDatabase &database);
    ~SqlQuery() {}

    SqlQuery &operator=(const SqlQuery &other);

    /*
     *  QSqlQuery related functions
     */
    bool isValid() const;
    bool isActive() const;
    bool qryIsNull(int field) const;
    bool qryIsNull(const QString &name) const;
    int qryAt() const;
    QString qryLastQuery() const;
    int qryNumRowsAffected() const;
//    QString qryLastError() const;
    bool qryIsSelect() const;
    int qrySize() const;
    bool qryIsForwardOnly() const;
    void qrySetForwardOnly(bool forward);
    bool qryExec(const QString& query);
    QVariant qryValue(int i) const;
    QVariant qryValue(const QString& name) const;
//    void qrySetNumericalPrecisionPolicy(NumericalPrecisionPolicy precisionPolicy);
//    NumericalPrecisionPolicy qryNumericalPrecisionPolicy() const;
    bool qrySeek(int i, bool relative = false);
    bool qryNext();
    bool qryPrevious();
    bool qryFirst();
    bool qryLast();
    void qryClear();

    // prepared query support
    bool qryExec();
//    bool execBatch(BatchExecutionMode mode = ValuesAsRows);
    bool qryPrepare(const QString& query);
//    void qryBindValue(const QString& placeholder, const QVariant& val, ParamType type = In);
//    void qryBindValue(int pos, const QVariant& val, ParamType type = In);
//    void qryAddBindValue(const QVariant& val, ParamType type = In);
    QVariant qryBoundValue(const QString& placeholder) const;
    QVariant qryBoundValue(int pos) const;
    QMap<QString, QVariant> boundValues() const;
    QString qryExecutedQuery() const;
    QVariant qryLastInsertId() const;
    void qryFinish();
    bool qryNextResult();
};

#endif // SQLQUERY_H
