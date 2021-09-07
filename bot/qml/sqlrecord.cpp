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

#include "sqlrecord.h"


const QString SqlRecord::TYPE_NAME = "SqlRecord";

SqlRecord::SqlRecord(const QSqlRecord &other) {
    _sqlRecord = other;
}

SqlRecord::SqlRecord(const SqlRecord &other) {
    _sqlRecord = other._sqlRecord;
}

SqlRecord::SqlRecord(SqlRecord *other) {
    _sqlRecord = other->_sqlRecord;
}

SqlRecord
&SqlRecord::operator=(const SqlRecord &other) {
    if (this == &other) {
        return *this;
    }

    _sqlRecord = other._sqlRecord;

    return *this;
}

bool
SqlRecord::operator==(const SqlRecord &other) const {
    return _sqlRecord == other._sqlRecord;
}

QVariant
SqlRecord::value(int i) const {
    return _sqlRecord.value(i);
}

QVariant
SqlRecord::value(const QString &name) const {
    return _sqlRecord.value(name);
}

void
SqlRecord::setValue(int i, const QVariant &val) {
    _sqlRecord.setValue(i, val);
}

void
SqlRecord::setValue(const QString &name, const QVariant &val) {
    _sqlRecord.setValue(name, val);
}

void
SqlRecord::setNull(int i) {
    _sqlRecord.setNull(i);
}

void
SqlRecord::setNull(const QString &name) {
    _sqlRecord.setNull(name);
}

bool
SqlRecord::isNull(int i) const {
    return _sqlRecord.isNull(i);
}

bool
SqlRecord::isNull(const QString &name) const {
    return _sqlRecord.isNull(name);
}

int
SqlRecord::indexOf(const QString &name) const {
    return _sqlRecord.indexOf(name);
}

QString
SqlRecord::fieldName(int i) const {
    return _sqlRecord.fieldName(i);
}

SqlField
SqlRecord::field(int i) const {
    return SqlField(_sqlRecord.field(i));
}

SqlField
SqlRecord::field(const QString &name) const {
    return SqlField(_sqlRecord.field(name));
}

bool
SqlRecord::isGenerated(int i) const {
    return _sqlRecord.isGenerated(i);
}

bool
SqlRecord::isGenerated(const QString &name) const {
    return _sqlRecord.isGenerated(name);
}

void
SqlRecord::setGenerated(const QString &name, bool generated) {
    _sqlRecord.setGenerated(name, generated);
}

void
SqlRecord::setGenerated(int i, bool generated) {
    _sqlRecord.setGenerated(i, generated);
}

void
SqlRecord::append(SqlField &field) {
    _sqlRecord.append(field.sqlField());
}

QSqlRecord
SqlRecord::sqlRecord() {
    return _sqlRecord;
}

void
SqlRecord::replace(int pos, SqlField &field) {
    _sqlRecord.replace(pos, field.sqlField());
}

void
SqlRecord::insert(int pos, SqlField &field) {
    _sqlRecord.insert(pos, field.sqlField());
}

void
SqlRecord::remove(int pos) {
    _sqlRecord.remove(pos);
}

bool
SqlRecord::isEmpty() const {
    return _sqlRecord.isEmpty();
}

bool
SqlRecord::contains(const QString &name) const {
    return _sqlRecord.contains(name);
}

void
SqlRecord::clear() {
    _sqlRecord.clear();
}

void
SqlRecord::clearValues() {
    _sqlRecord.clearValues();
}

int
SqlRecord::count() const {
    return _sqlRecord.count();
}

SqlRecord
SqlRecord::keyValues(SqlRecord &keyFields) const {
    return SqlRecord(_sqlRecord.keyValues(keyFields.sqlRecord()));
}
