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

#ifndef REACTION_H
#define REACTION_H

#include "jsonserializable.h"


class Reaction : public JsonSerializable
{
    Q_OBJECT
public:
    static const QString EMOJI;
    static const QString COUNT;
    static const QString ME;

    Reaction() {}
    Reaction(const QByteArray &json) : JsonSerializable(json) {}
    Reaction(const QJsonObject &json) : JsonSerializable(json) {}
    Reaction(const QString &json) : JsonSerializable(json) {}

    QJsonObject getEmoji() const;
    QJsonValue getCount() const;
    QJsonValue getMe() const;
    void setCount(const QJsonValue &count);
    void setEmoji(const QJsonObject &emoji);
    void setMe(const QJsonValue &me);

    Q_PROPERTY(QJsonValue count READ getCount WRITE setCount)
    Q_PROPERTY(QJsonValue me READ getMe WRITE setMe)
    Q_PROPERTY(QJsonObject emoji READ getEmoji WRITE setEmoji)
};

Q_DECLARE_METATYPE(Reaction)

#endif // REACTION_H
