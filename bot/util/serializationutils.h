/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SERIALIZATIONUTILS_H
#define SERIALIZATIONUTILS_H

#include "logging/logfactory.h"
#include "payloads/jsonserializable.h"
#include <QMetaProperty>

struct SerializationUtils
{
    static void readFromJson(QObject &target, const QJsonObject &source);
    static void writeToJson(const QObject &source, QJsonObject &target);
    static QJsonObject toQJsonObject(const QObject &source);
    static QString toQString(const QObject &source);
    static QByteArray toQByteArray(const QObject &source);
    static QByteArray toQByteArray(const QJsonObject &source);
    static QJsonDocument toJsonDocument(const QObject &source);
    static QVariant toVariant(const QObject &source);
    static void fromQJsonObject(QObject &target, const QJsonObject &source);
    static void fromQString(QObject &target, const QString &source);
    static void fromQByteArray(QObject &target, const QByteArray &source);
    static void fromJsonDocument(QObject &target, const QJsonDocument &source);
    static void fromVariant(QObject &target, const QVariant &source);
};

#endif // SERIALIZATIONUTILS_H
