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

#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include "jsonserializable.h"


class ActivityTimestamps : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString START;
    static const QString END;

    ActivityTimestamps() {}
    ActivityTimestamps(const QByteArray &json) : JsonSerializable(json) {}
    ActivityTimestamps(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityTimestamps(const QString &json) : JsonSerializable(json) {}

    void setEnd(const QJsonValue &end);
    void setStart(const QJsonValue &start);
    QJsonValue getEnd() const;
    QJsonValue getStart() const;

    Q_PROPERTY(QJsonValue start READ getStart WRITE setStart)
    Q_PROPERTY(QJsonValue end READ getEnd WRITE setEnd)
};

Q_DECLARE_METATYPE(ActivityTimestamps)

#endif // TIMESTAMPS_H
