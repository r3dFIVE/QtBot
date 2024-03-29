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

#ifndef GUILDROLEDELETE_H
#define GUILDROLEDELETE_H

#include "jsonserializable.h"

class GuildRoleDelete : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString GUILD_ID;
    static const QString ROLE_ID;

    GuildRoleDelete(QObject *parent = nullptr) : JsonSerializable(parent) {}
    GuildRoleDelete(const GuildRoleDelete &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    GuildRoleDelete(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    GuildRoleDelete(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    GuildRoleDelete(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getGuildId() const;
    QJsonValue getRoleId() const;
    void setGuildId(const QJsonValue &guildId);
    void setRoleId(const QJsonValue &roleId);
};

Q_DECLARE_METATYPE(GuildRoleDelete)

#endif // GUILDROLEDELETE_H
