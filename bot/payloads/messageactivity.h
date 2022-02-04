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

#ifndef MESSAGEACTIVITY_H
#define MESSAGEACTIVITY_H

#include "jsonserializable.h"


class MessageActivity : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString PARTY_ID;
    static const QString TYPE;

    MessageActivity(QObject *parent = nullptr) : JsonSerializable(parent) {}
    MessageActivity(const MessageActivity &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    MessageActivity(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    MessageActivity(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    MessageActivity(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getPartyId() const;
    QJsonValue getType() const;
    void setPartyId(const QJsonValue &partyId);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue party_id READ getPartyId WRITE setPartyId)
};

Q_DECLARE_METATYPE(MessageActivity)

#endif // MESSAGEACTIVITY_H
