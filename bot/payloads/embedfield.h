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

    EmbedField() {}
    EmbedField(const QByteArray &json) : JsonSerializable(json) {}
    EmbedField(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedField(const QString &json) : JsonSerializable(json) {}

    QJsonValue getInline() const;
    QJsonValue getName() const;
    QJsonValue getValue() const;
    void setName(const QJsonValue &name);
    void setValue(const QJsonValue &value);
    void setInline(const QJsonValue &inln);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue value READ getValue WRITE setValue)
    Q_PROPERTY(QJsonValue inline READ getInline WRITE setInline)
};

Q_DECLARE_METATYPE(EmbedField)

#endif // EMBEDFIELD_H
