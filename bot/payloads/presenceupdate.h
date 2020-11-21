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

#ifndef PRESENCE_H
#define PRESENCE_H

#include "jsonserializable.h"


class PresenceUpdate : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString USER;
    static const QString ROLES;
    static const QString GAME;
    static const QString GUILD_ID;
    static const QString STATUS;
    static const QString ACTIVITIES;
    static const QString CLIENT_STATUS;
    static const QString PREMIUM_SINCE;
    static const QString NICK;

    PresenceUpdate() {}
    PresenceUpdate(const QByteArray &json) : JsonSerializable(json) {}
    PresenceUpdate(const QJsonObject &json) : JsonSerializable(json) {}
    PresenceUpdate(const QString &json) : JsonSerializable(json) {}

    QJsonArray getActivities() const;
    QJsonArray getRoles() const;
    QJsonObject getClientStatus() const;
    QJsonObject getUser() const;
    QJsonObject getGame() const;
    QJsonValue getGuildId() const;
    QJsonValue getNick() const;
    QJsonValue getPremiumSince() const;
    QJsonValue getStatus() const;
    void setActivities(const QJsonArray &activities);
    void setClientStatus(const QJsonObject &clientStatus);
    void setGame(const QJsonObject &game);
    void setGuildId(const QJsonValue &guildId);
    void setNick(const QJsonValue &nick);
    void setPremiumSince(const QJsonValue &premiumSince);
    void setRoles(const QJsonArray &roles);
    void setStatus(const QJsonValue &status);
    void setUser(const QJsonObject &user);

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    Q_PROPERTY(QJsonObject game READ getGame WRITE setGame)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue status READ getStatus WRITE setStatus)
    Q_PROPERTY(QJsonArray activities READ getActivities WRITE setActivities)
    Q_PROPERTY(QJsonObject client_status READ getClientStatus WRITE setClientStatus)
    Q_PROPERTY(QJsonValue premium_since READ getPremiumSince WRITE setPremiumSince)
    Q_PROPERTY(QJsonValue nick READ getNick WRITE setNick)
};

Q_DECLARE_METATYPE(PresenceUpdate)

#endif // PRESENCE_H
