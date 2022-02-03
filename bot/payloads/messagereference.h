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

#ifndef MESSAGEREFERENCE_H
#define MESSAGEREFERENCE_H

#include "jsonserializable.h"


class MessageReference : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString CHANNEL_ID;
    static const QString GUILD_ID;
    static const QString MESSAGE_ID;

    MessageReference(QObject *parent = nullptr) : JsonSerializable(parent) {}
    MessageReference(const MessageReference &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    MessageReference(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    MessageReference(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    MessageReference(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getChannelId() const;
    QJsonValue getGuildId() const;
    QJsonValue getMessageId() const;
    void setChannelId(const QJsonValue &channelId);
    void setGuildId(const QJsonValue &guildId);
    void setMessageId(const QJsonValue &messageId);

    Q_PROPERTY(QJsonValue message_id READ getMessageId WRITE setMessageId)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
};

Q_DECLARE_METATYPE(MessageReference)


#endif // MESSAGEREFERENCE_H
