#ifndef SQLRECORD_H
#define SQLRECORD_H

#include <QObject>
#include <QSqlRecord>
#include <QVariant>

#include "sqlfield.h"

class SqlRecord : public QObject
{
    Q_OBJECT

    QSqlRecord _sqlRecord;

public:
    Q_INVOKABLE SqlRecord() {}
    Q_INVOKABLE SqlRecord(const QSqlRecord &other);
    Q_INVOKABLE SqlRecord(const SqlRecord& other);
    Q_INVOKABLE SqlRecord(SqlRecord *other);
    Q_INVOKABLE ~SqlRecord() {}
    Q_INVOKABLE SqlRecord& operator=(const SqlRecord& other);
    Q_INVOKABLE bool operator==(const SqlRecord &other) const;
    Q_INVOKABLE bool operator!=(const SqlRecord &other) const {
        return _sqlRecord != other._sqlRecord;
    }
    Q_INVOKABLE QVariant value(int i) const;
    Q_INVOKABLE QVariant value(const QString& name) const;
    Q_INVOKABLE void setValue(int i, const QVariant& val);
    Q_INVOKABLE void setValue(const QString& name, const QVariant& val);
    Q_INVOKABLE void setNull(int i);
    Q_INVOKABLE void setNull(const QString& name);
    Q_INVOKABLE bool isNull(int i) const;
    Q_INVOKABLE bool isNull(const QString& name) const;
    Q_INVOKABLE int indexOf(const QString &name) const;
    Q_INVOKABLE QString fieldName(int i) const;
    Q_INVOKABLE SqlField field(int i) const;
    Q_INVOKABLE SqlField field(const QString &name) const;
    Q_INVOKABLE bool isGenerated(int i) const;
    Q_INVOKABLE bool isGenerated(const QString& name) const;
    Q_INVOKABLE void setGenerated(const QString& name, bool generated);
    Q_INVOKABLE void setGenerated(int i, bool generated);
    Q_INVOKABLE void append(SqlField &field);
    Q_INVOKABLE void replace(int pos, SqlField& field);
    Q_INVOKABLE void insert(int pos, SqlField& field);
    Q_INVOKABLE void remove(int pos);
    Q_INVOKABLE bool isEmpty() const;
    Q_INVOKABLE bool contains(const QString& name) const;
    Q_INVOKABLE void clear();
    Q_INVOKABLE void clearValues();
    Q_INVOKABLE int count() const;
    Q_INVOKABLE QSqlRecord sqlRecord();
    Q_INVOKABLE SqlRecord keyValues(SqlRecord &keyFields) const;
};

Q_DECLARE_METATYPE(SqlRecord)

#endif // SQLRECORD_H
