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

#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"


class Emoji : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString NAME;
    static const QString ROLES;
    static const QString USER;
    static const QString REQUIRE_COLONS;
    static const QString MANAGED;
    static const QString ANIMATED;
    static const QString AVAILABLE;

    Emoji(QObject *parent = nullptr) : JsonSerializable(parent) {}
    Emoji(const Emoji &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    Emoji(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Emoji(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Emoji(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonArray getRoles() const;
    QJsonObject getUser() const;
    QJsonValue getAnimated() const;
    QJsonValue getAvailable() const;
    QJsonValue getId() const;
    QJsonValue getManaged() const;
    QJsonValue getName() const;
    QJsonValue getRequireColons() const;
    void setAnimated(const QJsonValue &animated);
    void setAvailable(const QJsonValue &available);
    void setId(const QJsonValue &id);
    void setManaged(const QJsonValue &managed);
    void setName(const QJsonValue &name);
    void setRequireColons(const QJsonValue &requireColons);
    void setRoles(const QJsonArray &roles);
    void setUser(const QJsonObject &user);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    Q_PROPERTY(QJsonValue require_colons READ getRequireColons WRITE setRequireColons)
    Q_PROPERTY(QJsonValue managed READ getManaged WRITE setManaged)
    Q_PROPERTY(QJsonValue animated READ getAnimated WRITE setAnimated)
    Q_PROPERTY(QJsonValue available READ getAvailable WRITE setAvailable)
};

#endif // EMOJI_H
