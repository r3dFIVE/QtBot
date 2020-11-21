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

#ifndef GUILDMEMBER_H
#define GUILDMEMBER_H

#include "jsonserializable.h"


class GuildMember : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString USER;
    static const QString NICK;
    static const QString ROLES;
    static const QString JOINED_AT;
    static const QString PREMIUM_SINCE;
    static const QString DEAF;
    static const QString MUTE;

    GuildMember() {}
    GuildMember(const QByteArray &json) : JsonSerializable(json) {}
    GuildMember(const QJsonObject &json) : JsonSerializable(json) {}
    GuildMember(const QString &json) : JsonSerializable(json) {}

    QJsonArray getRoles() const;
    QJsonObject getUser() const;
    QJsonValue getDeaf() const;
    QJsonValue getJoinedAt() const;
    QJsonValue getMute() const;
    QJsonValue getNick() const;
    QJsonValue getPremiumSince() const;
    void setUser(const QJsonObject &user);
    void setNick(const QJsonValue &nick);
    void setRoles(const QJsonArray &roles);
    void setJoinedAt(const QJsonValue &joinedAt);
    void setPremiumSince(const QJsonValue &premiumSince);
    void setDeaf(const QJsonValue &deaf);
    void setMute(const QJsonValue &mute);

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    Q_PROPERTY(QJsonValue nick READ getNick WRITE setNick)
    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    Q_PROPERTY(QJsonValue joined_at READ getJoinedAt WRITE setJoinedAt)
    Q_PROPERTY(QJsonValue premium_since READ getPremiumSince WRITE setPremiumSince)
    Q_PROPERTY(QJsonValue deaf READ getDeaf WRITE setDeaf)
    Q_PROPERTY(QJsonValue mute READ getMute WRITE setDeaf)
};

Q_DECLARE_METATYPE(GuildMember)

#endif // GUILDMEMBER_H
