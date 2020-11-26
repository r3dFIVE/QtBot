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

#ifndef READY_H
#define READY_H

#include "jsonserializable.h"


class Ready : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString V;
    static const QString USER;
    static const QString PRIVATE_CHANNELS;
    static const QString GUILDS;
    static const QString SESSION_ID;
    static const QString SHARD;

    Ready() {}
    Ready(const QByteArray &json) : JsonSerializable(json) {}
    Ready(const QJsonObject &json) : JsonSerializable(json) {}
    Ready(const QString &json) : JsonSerializable(json) {}

    QJsonArray getShard() const;
    QJsonArray getGuilds() const;
    QJsonArray getPrivateChannels() const;
    QJsonObject getUser() const;
    QJsonValue getSessionId() const;
    QJsonValue getV() const;
    void setGuilds(const QJsonArray &guilds);
    void setPrivateChannels(const QJsonArray &privateChannels);
    void setSessionId(const QJsonValue &sessionId);
    void setShard(const QJsonArray &shard);
    void setUser(const QJsonObject &user);
    void setV(const QJsonValue &v);

    Q_PROPERTY(QJsonValue v READ getV WRITE setV)
    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    Q_PROPERTY(QJsonArray private_channels READ getPrivateChannels WRITE setPrivateChannels)
    Q_PROPERTY(QJsonArray guilds READ getGuilds WRITE setGuilds)
    Q_PROPERTY(QJsonValue session_id READ getSessionId WRITE setSessionId)
    Q_PROPERTY(QJsonArray shard READ getShard WRITE setShard)
};

Q_DECLARE_METATYPE(Ready)

#endif // READY_H
