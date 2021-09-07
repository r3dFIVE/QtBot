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

#include "sqlfield.h"


const QString SqlField::TYPE_NAME = "SqlField";

SqlField::SqlField(const QString &fieldName, QVariant::Type type) {
    _sqlField = QSqlField(fieldName, type);
}

SqlField::SqlField(const QString &fieldName, QVariant::Type type, const QString &tableName) {
    _sqlField = QSqlField(fieldName, type, tableName);
}

SqlField::SqlField(const QSqlField &other) {
    _sqlField = other;
}

SqlField::SqlField(SqlField *sqlField) {
    _sqlField = sqlField->_sqlField;
}

SqlField::SqlField(const SqlField &other) {
    _sqlField = other._sqlField;
}

SqlField &SqlField::operator=(const SqlField &other) {
    if (this == &other) {
        return *this;
    }

    _sqlField = other._sqlField;

    return *this;
}

bool
SqlField::operator==(const SqlField &other) const {
    return _sqlField == other._sqlField;
}

void
SqlField::setValue(const QVariant &value) {
    _sqlField.setValue(value);
}

void
SqlField::setName(const QString &name) {
    _sqlField.setName(name);
}

QString
SqlField::name() const {
    return _sqlField.name();
}

void
SqlField::setTableName(const QString &tableName) {
    _sqlField.setTableName(tableName);
}

QString
SqlField::tableName() const {
    return _sqlField.tableName();
}

bool
SqlField::isNull() const {
    return _sqlField.isNull();
}

void
SqlField::setReadOnly(bool readOnly) {
    _sqlField.setReadOnly(readOnly);
}

bool
SqlField::isReadOnly() const {
    return _sqlField.isReadOnly();
}

void
SqlField::clear() {
    _sqlField.clear();
}

QVariant::Type
SqlField::type() const {
    return _sqlField.type();
}

bool
SqlField::isAutoValue() const {
    return _sqlField.isAutoValue();
}

void
SqlField::setType(QVariant::Type type) {
    _sqlField.setType(type);
}

void
SqlField::setRequiredStatus(Sql::RequiredStatus status) {
    _sqlField.setRequiredStatus(QSqlField::RequiredStatus(status));
}

void
SqlField::setLength(int fieldLength) {
    _sqlField.setLength(fieldLength);
}

void
SqlField::setPrecision(int precision) {
    _sqlField.setPrecision(precision);
}

void
SqlField::setDefaultValue(const QVariant &value) {
    _sqlField.setValue(value);
}

void
SqlField::setSqlType(int type) {
    _sqlField.setSqlType(type);
}

void
SqlField::setGenerated(bool gen) {
    _sqlField.setGenerated(gen);
}

void
SqlField::setAutoValue(bool autoVal) {
    _sqlField.setAutoValue(autoVal);
}

QSqlField
SqlField::sqlField() {
    return _sqlField;
}

Sql::RequiredStatus
SqlField::requiredStatus() const {
    return Sql::RequiredStatus(_sqlField.requiredStatus());
}

int
SqlField::length() const {
    return _sqlField.length();
}

int
SqlField::precision() const {
    return _sqlField.precision();
}

QVariant
SqlField::defaultValue() const {
    return _sqlField.defaultValue();
}

int
SqlField::typeID() const {
    return _sqlField.typeID();
}

bool
SqlField::isGenerated() const {
    return _sqlField.isGenerated();
}

bool
SqlField::isValid() const {
    return _sqlField.isValid();
}
