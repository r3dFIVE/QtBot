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

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "jsonserializable.h"


class Activity : public JsonSerializable
{
    Q_OBJECT

public:
    enum ActivityType {
        Game = 0,
        Streaming = 1,
        Listening = 2,
        Custom = 4
    };
    Q_ENUM(ActivityType)

    static const QString NAME;
    static const QString TYPE;
    static const QString URL;
    static const QString CREATED_AT;
    static const QString TIMESTAMPS;
    static const QString APPLICATION_ID;
    static const QString DETAILS;
    static const QString STATE;
    static const QString EMOJI;
    static const QString PARTY;
    static const QString ASSETS;
    static const QString SECRETS;
    static const QString INSTANCE;
    static const QString FLAGS;

    Activity() {}
    Activity(const QByteArray &json) : JsonSerializable(json) {}
    Activity(const QJsonObject &json) : JsonSerializable(json) {}
    Activity(const QString &json) : JsonSerializable(json) {}

    QJsonObject getAssets() const;
    QJsonObject getEmoji() const;
    QJsonObject getParty() const;
    QJsonObject getSecrets() const;
    QJsonObject getTimestamps() const;
    QJsonValue getApplicationId() const;
    QJsonValue getCreatedAt() const;
    QJsonValue getDetails() const;
    QJsonValue getFlags() const;
    QJsonValue getInstance() const;
    QJsonValue getName() const;
    QJsonValue getState() const;
    QJsonValue getType() const;
    QJsonValue getUrl() const;
    void setApplicationId(const QJsonValue &application_id);
    void setAssets(const QJsonObject &assets);
    void setCreatedAt(const QJsonValue &created_at);
    void setDetails(const QJsonValue &details);
    void setEmoji(const QJsonObject &emoji);
    void setFlags(const QJsonValue &flags);
    void setInstance(const QJsonValue &instance);
    void setName(const QJsonValue &name);
    void setParty(const QJsonObject &party);
    void setSecrets(const QJsonObject &secrets);
    void setState(const QJsonValue &state);
    void setTimestamps(const QJsonObject &timestamps);
    void setType(const QJsonValue &type);
    void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue created_at READ getCreatedAt WRITE setCreatedAt)
    Q_PROPERTY(QJsonObject timestamps  READ getTimestamps WRITE setTimestamps)
    Q_PROPERTY(QJsonValue application_id READ getApplicationId WRITE setApplicationId)
    Q_PROPERTY(QJsonValue details READ getDetails WRITE setDetails)
    Q_PROPERTY(QJsonValue state READ getState WRITE setState)
    Q_PROPERTY(QJsonObject emoji READ getEmoji WRITE setEmoji)
    Q_PROPERTY(QJsonObject party READ getParty WRITE setParty)
    Q_PROPERTY(QJsonObject assets READ getAssets WRITE setAssets)
    Q_PROPERTY(QJsonObject secrets READ getSecrets WRITE setSecrets)
    Q_PROPERTY(QJsonValue instance READ getInstance WRITE setInstance)
    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
};

Q_DECLARE_METATYPE(Activity)

#endif // ACTIVITY_H
