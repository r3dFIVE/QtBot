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

#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "jsonserializable.h"


class Identify : public JsonSerializable
{

    Q_OBJECT
public:
    static const QString TOKEN;
    static const QString PROPERTIES;
    static const QString COMPRESS;
    static const QString LARGE_THRESHOLD;
    static const QString SHARD;
    static const QString PRESENCE;
    static const QString GUILD_SUBSCRIPTIONS;
    static const QString INTENTS;

    Identify() {}
    Identify(const QByteArray &json) : JsonSerializable(json) {}
    Identify(const QJsonObject &json) : JsonSerializable(json) {}
    Identify(const QString &json) : JsonSerializable(json) {}

    QJsonArray getShard() const;
    QJsonObject getPresence() const;
    QJsonObject getProperties() const;
    QJsonValue getCompress() const;
    QJsonValue getGuildSubscriptions() const;
    QJsonValue getIntents() const;
    QJsonValue getLargeThreshold() const;
    QJsonValue getToken() const;
    void setCompress(const QJsonValue &getCompress);
    void setGuildSubscriptions(const QJsonValue &getGuildSubscriptions);
    void setIntents(const QJsonValue &getIntents);
    void setLargeThreshold(const QJsonValue &getLargeThreshold);
    void setPresence(const QJsonObject &getPresence);
    void setProperties(const QJsonObject &getProperties);
    void setShard(const QJsonArray &getShard);
    void setToken (const QJsonValue &getToken);

    Q_PROPERTY(QJsonValue getToken READ getToken WRITE setToken)
    Q_PROPERTY(QJsonObject getProperties READ getProperties WRITE setProperties)
    Q_PROPERTY(QJsonValue getCompress READ getCompress WRITE setCompress)
    Q_PROPERTY(QJsonValue large_threshold READ getLargeThreshold WRITE setLargeThreshold)
    Q_PROPERTY(QJsonArray getShard READ getShard WRITE setShard)
    Q_PROPERTY(QJsonObject getPresence READ getPresence WRITE setPresence)
    Q_PROPERTY(QJsonValue guild_subscriptions READ getGuildSubscriptions WRITE setGuildSubscriptions)
    Q_PROPERTY(QJsonValue getIntents READ getIntents WRITE setIntents)
};

Q_DECLARE_METATYPE(Identify)

#endif // IDENTIFY_H
