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

#ifndef EMBEDFIELD_H
#define EMBEDFIELD_H

#include "jsonserializable.h"


class EmbedField : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString INLINE;
    static const QString NAME;
    static const QString VALUE;

    EmbedField(QObject *parent = nullptr) : JsonSerializable(parent) {}
    EmbedField(const EmbedField &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    EmbedField(const QString &name,
               const QString &value,
               const bool isInline,
               QObject *parent = nullptr);
    EmbedField(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    EmbedField(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    EmbedField(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    Q_INVOKABLE QJsonValue getInline() const;
    Q_INVOKABLE QJsonValue getName() const;
    Q_INVOKABLE QJsonValue getValue() const;
    Q_INVOKABLE void setName(const QJsonValue &name);
    Q_INVOKABLE void setValue(const QJsonValue &value);
    Q_INVOKABLE void setInline(const QJsonValue &isInline);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue value READ getValue WRITE setValue)
    Q_PROPERTY(QJsonValue inline READ getInline WRITE setInline)
};

Q_DECLARE_METATYPE(EmbedField)

#endif // EMBEDFIELD_H
