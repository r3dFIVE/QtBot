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

#ifndef CHANNELMENTION_H
#define CHANNELMENTION_H

#include "jsonserializable.h"

#include <QObject>

class ChannelMention : public JsonSerializable
{
    Q_OBJECT

public:      
    static const QString ID;
    static const QString GUILD_ID;
    static const QString TYPE;
    static const QString NAME;

    ChannelMention() {}
    ChannelMention(const QByteArray &json) : JsonSerializable(json) {}
    ChannelMention(const QJsonObject &json) : JsonSerializable(json) {}
    ChannelMention(const QString &json) : JsonSerializable(json) {}

    QJsonValue getGuildId() const;
    QJsonValue getId() const;
    QJsonValue getName() const;
    QJsonValue getType() const;
    void setGuildId(const QJsonValue &guild_id);
    void setId(const QJsonValue &id);
    void setName(const QJsonValue &name);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
};

Q_DECLARE_METATYPE(ChannelMention)

#endif // CHANNELMENTION_H
