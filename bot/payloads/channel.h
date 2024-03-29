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

#ifndef CHANNEL_H
#define CHANNEL_H

#include "jsonserializable.h"


class Channel : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString TYPE;
    static const QString GUILD_ID;
    static const QString POSITION;
    static const QString PERMISSION_OVERWRITES ;
    static const QString NAME;
    static const QString TOPIC;
    static const QString NSFW;
    static const QString LAST_MESSAGE_ID;
    static const QString BITRATE;
    static const QString USER_LIMIT;
    static const QString RATE_LIMIT_PER_USER;
    static const QString RECIPIENTS;
    static const QString ICON;
    static const QString OWNER_ID;
    static const QString APPLICATION_ID;
    static const QString PARENT_ID;
    static const QString LAST_PIN_TIMESTAMP;

    Channel(QObject *parent = nullptr) : JsonSerializable(parent) {}
    Channel(const Channel &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    Channel(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Channel(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Channel(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getApplicationId() const;
    QJsonValue getBitrate() const;
    QJsonValue getGuildId() const;
    QJsonValue getIcon() const;
    QJsonValue getId() const;
    QJsonValue getLastMessageId() const;
    QJsonValue getLastPinTimestamp() const;
    QJsonValue getOwnerId() const;
    QJsonValue getName() const;
    QJsonValue getNsfw() const;
    QJsonValue getParentId() const;
    QJsonValue getPosition() const;
    QJsonValue getRateLimitPerUser() const;
    QJsonValue getTopic() const;
    QJsonValue getType() const;
    QJsonValue getUserLimit() const;
    QJsonArray getRecipients() const;
    QJsonArray getPermissionOverwrites() const;
    void setId(const QJsonValue &id);
    void setType(const QJsonValue &type);
    void setGuildId(const QJsonValue &guildId);
    void setPosition(const QJsonValue &position);
    void setPermissionOverwrites(const QJsonArray &permissionOverwrites);
    void setName(const QJsonValue &name);
    void setTopic(const QJsonValue &topic);
    void setNsfw(const QJsonValue &nsfw);
    void setLastMessageId(const QJsonValue &lastMessageId);
    void setBitrate(const QJsonValue &bitrate);
    void setUserLimit(const QJsonValue &userLimit);
    void setRateLimitPerUser(const QJsonValue &rateLimitPerUser);
    void setRecipients(const QJsonArray &recipients);
    void setIcon(const QJsonValue &icon);
    void setOwnerId(const QJsonValue &ownerId);
    void setApplicationId(const QJsonValue &applicationId);
    void  setParentId(const QJsonValue &parentId);
    void setLastPinTimestamp(const QJsonValue &lastPinTimestamp);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue position READ getPosition WRITE setPosition)
    Q_PROPERTY(QJsonArray permission_overwrites READ getPermissionOverwrites WRITE setPermissionOverwrites)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue topic READ getTopic WRITE setTopic)
    Q_PROPERTY(QJsonValue nsfw READ getNsfw WRITE setNsfw)
    Q_PROPERTY(QJsonValue last_message_id READ getLastMessageId WRITE setLastMessageId)
    Q_PROPERTY(QJsonValue bitrate READ getBitrate WRITE setBitrate)
    Q_PROPERTY(QJsonValue user_limit READ getUserLimit WRITE setUserLimit)
    Q_PROPERTY(QJsonValue rate_limit_per_user READ getRateLimitPerUser WRITE setRateLimitPerUser)
    Q_PROPERTY(QJsonArray recipients READ getRecipients WRITE setRecipients)
    Q_PROPERTY(QJsonValue icon READ getIcon WRITE setIcon)
    Q_PROPERTY(QJsonValue owner_id READ getOwnerId WRITE setOwnerId)
    Q_PROPERTY(QJsonValue application_id READ getApplicationId WRITE setApplicationId)
    Q_PROPERTY(QJsonValue parent_id READ getParentId WRITE setParentId)
    Q_PROPERTY(QJsonValue last_pin_timestamp READ getLastPinTimestamp WRITE setLastPinTimestamp)
};

Q_DECLARE_METATYPE(Channel)

#endif // CHANNEL_H
