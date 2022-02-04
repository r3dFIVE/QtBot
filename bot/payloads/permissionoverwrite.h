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

#ifndef PERMISSIONOVERWRITES_H
#define PERMISSIONOVERWRITES_H

#include "jsonserializable.h"


class PermissionOverwrite : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString TYPE;
    static const QString ALLOW;
    static const QString DENY;

    PermissionOverwrite(QObject *parent = nullptr) : JsonSerializable(parent) {}
    PermissionOverwrite(const PermissionOverwrite &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    PermissionOverwrite(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    PermissionOverwrite(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    PermissionOverwrite(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getAllow() const;
    QJsonValue getDeny() const;
    QJsonValue getId() const;
    QJsonValue getType() const;
    void setAllow(const QJsonValue &allow);
    void setDeny(const QJsonValue &deny);
    void setId(const QJsonValue &id);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue allow READ getAllow WRITE setAllow)
    Q_PROPERTY(QJsonValue deny READ getDeny WRITE setDeny)
};

Q_DECLARE_METATYPE(PermissionOverwrite)

#endif // PERMISSIONOVERWRITES_H
