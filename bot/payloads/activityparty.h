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

#ifndef PARTY_H
#define PARTY_H

#include "jsonserializable.h"


class ActivityParty : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString SIZE;

    ActivityParty() {}
    ActivityParty(const QByteArray &json) : JsonSerializable(json) {}
    ActivityParty(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityParty(const QString &json) : JsonSerializable(json) {}

    QJsonArray getSize() const;
    QJsonValue getId() const;
    void setId(const QJsonValue &id);
    void setSize(const QJsonArray &size);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonArray size READ getSize WRITE setSize)
};

Q_DECLARE_METATYPE(ActivityParty)

#endif // PARTY_H
