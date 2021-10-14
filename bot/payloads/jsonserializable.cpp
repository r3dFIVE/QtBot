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

#include "jsonserializable.h"


JsonSerializable::JsonSerializable(const QJsonObject &json, QObject *parent) : QObject(parent) {
    _jsonObject = json;
}

JsonSerializable::JsonSerializable(const QString &json, QObject *parent) : QObject(parent) {
    _jsonObject = fromQString(json);
}

JsonSerializable::JsonSerializable(const QByteArray &json, QObject *parent) : QObject(parent) {
    _jsonObject = fromByteArray(json);
}

void
JsonSerializable::setQJsonObject(const QJsonObject &jsonObject) {
    _jsonObject = jsonObject;
}

QJsonObject
JsonSerializable::object() {
    return _jsonObject;
}

QJsonObject
JsonSerializable::toQJsonObject() {
    return _jsonObject;
}

QByteArray
JsonSerializable::toByteArray() {
    QJsonDocument document(_jsonObject);

    return document.toJson(QJsonDocument::Compact);
}

QString
JsonSerializable::toQString() {
    return QString(toByteArray());
}

QJsonObject
JsonSerializable::fromQString(const QString &json) {
    return fromByteArray(json.toUtf8());
}

QJsonObject
JsonSerializable::fromByteArray(const QByteArray &json) {
    QJsonDocument document = QJsonDocument::fromJson(json);

    QJsonObject jsonObject = document.object();

    _jsonObject = jsonObject;

    return _jsonObject;
}
