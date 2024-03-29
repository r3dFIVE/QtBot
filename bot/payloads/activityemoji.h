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

#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializable.h"


class ActivityEmoji : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString NAME;
    static const QString ID;
    static const QString ANIMATED;

    ActivityEmoji(QObject *parent = nullptr) : JsonSerializable(parent) {}
    ActivityEmoji(const ActivityEmoji &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    ActivityEmoji(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    ActivityEmoji(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    ActivityEmoji(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    QJsonValue getAnimated() const;
    QJsonValue getId() const;
    QJsonValue getName() const;
    void setAnimated(const QJsonValue &animated);
    void setId(const QJsonValue &id);
    void setName(const QJsonValue &name);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue animated READ getAnimated WRITE setAnimated)
};

Q_DECLARE_METATYPE(ActivityEmoji)

#endif // EMOJI_H
