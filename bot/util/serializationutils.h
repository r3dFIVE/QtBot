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

#ifndef SERIALIZATIONUTILS_H
#define SERIALIZATIONUTILS_H

#include "payloads/jsonserializable.h"

struct SerializationUtils
{
    static void readFromJson(JsonSerializable &target, const QJsonObject &source);
    static void writeToJson(const JsonSerializable &source, QJsonObject &target);
    static QJsonObject toQJsonObject(const QString &source);
    static QJsonObject toQJsonObject(const JsonSerializable &source);
    static QString toQString(const JsonSerializable &source);
    static QByteArray toQByteArray(const JsonSerializable &source);
    static QByteArray toQByteArray(const QJsonObject &source);
    static QJsonDocument toJsonDocument(const JsonSerializable &source);
    static QVariant toVariant(const JsonSerializable &source);
    static void fromQJsonObject(JsonSerializable &target, const QJsonObject &source);
    static void fromQString(JsonSerializable &target, const QString &source);
    static void fromQByteArray(JsonSerializable &target, const QByteArray &source);
    static void fromJsonDocument(JsonSerializable &target, const QJsonDocument &source);
    static void fromVariant(JsonSerializable &target, const QVariant &source);
    static QJsonObject xmlToQJsonObject(const QString &xml);
};

#endif // SERIALIZATIONUTILS_H
