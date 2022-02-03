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

#ifndef GUILDROLEUPDATE_H
#define GUILDROLEUPDATE_H

#include <QObject>

#include "jsonserializable.h"


class GuildRoleUpdate : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString GUILD_ID;
    static const QString ROLE;

    GuildRoleUpdate(QObject *parent = nullptr) : JsonSerializable(parent) {}
    GuildRoleUpdate(const GuildRoleUpdate &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    GuildRoleUpdate(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    GuildRoleUpdate(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    GuildRoleUpdate(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getGuildId() const;
    QJsonObject getRole() const;
    void setGuildId(const QJsonValue &guildId);
    void setRole(const QJsonObject &object);

    Q_PROPERTY(QJsonObject role READ getRole WRITE setRole)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)

};

Q_DECLARE_METATYPE(GuildRoleUpdate)

#endif // GUILDROLEUPDATE_H
