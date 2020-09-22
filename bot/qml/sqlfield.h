#ifndef SQLFIELD_H
#define SQLFIELD_H

#include <QObject>
#include <QSqlField>

#include "enums/sql.h"

class SqlField : public QObject
{
    Q_OBJECT

    QSqlField _sqlField;

public:
    Q_INVOKABLE SqlField() {}
    Q_INVOKABLE SqlField(const QString& fieldName,
                       QVariant::Type type = {});
    Q_INVOKABLE SqlField(const QString &fieldName, QVariant::Type type,
              const QString &tableName);
    Q_INVOKABLE SqlField(const QSqlField &other);
    Q_INVOKABLE SqlField(const SqlField& other);
    Q_INVOKABLE SqlField(SqlField *sqlField);
    Q_INVOKABLE ~SqlField() {}
    Q_INVOKABLE SqlField& operator=(const SqlField& other);
    Q_INVOKABLE bool operator==(const SqlField& other) const;
    Q_INVOKABLE bool operator!=(const SqlField &other) const {
        return _sqlField != other._sqlField;
    }
    Q_INVOKABLE void setValue(const QVariant& value);
    Q_INVOKABLE QVariant value() const {
        return _sqlField.value();
    }
    Q_INVOKABLE void setName(const QString& name);
    Q_INVOKABLE QString name() const;
    Q_INVOKABLE void setTableName(const QString &tableName);
    Q_INVOKABLE QString tableName() const;
    Q_INVOKABLE bool isNull() const;
    Q_INVOKABLE void setReadOnly(bool readOnly);
    Q_INVOKABLE bool isReadOnly() const;
    Q_INVOKABLE void clear();
    Q_INVOKABLE QVariant::Type type() const;
    Q_INVOKABLE bool isAutoValue() const;
    Q_INVOKABLE void setType(QVariant::Type type);
    Q_INVOKABLE void setRequiredStatus(Sql::RequiredStatus status);
    Q_INVOKABLE  void setRequired(bool required) {
        setRequiredStatus(required ? Sql::Required : Sql::Optional);
    }
    Q_INVOKABLE void setLength(int fieldLength);
    Q_INVOKABLE void setPrecision(int precision);
    Q_INVOKABLE void setDefaultValue(const QVariant &value);
    Q_INVOKABLE void setSqlType(int type);
    Q_INVOKABLE void setGenerated(bool gen);
    Q_INVOKABLE void setAutoValue(bool autoVal);
    Q_INVOKABLE QSqlField sqlField();
    Q_INVOKABLE Sql::RequiredStatus requiredStatus() const;
    Q_INVOKABLE int length() const;
    Q_INVOKABLE int precision() const;
    Q_INVOKABLE QVariant defaultValue() const;
    Q_INVOKABLE int typeID() const;
    Q_INVOKABLE bool isGenerated() const;
    Q_INVOKABLE bool isValid() const;
};

#endif // SQLFIELD_H
