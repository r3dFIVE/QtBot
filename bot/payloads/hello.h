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

#ifndef HELLO_H
#define HELLO_H

#include "jsonserializable.h"


class Hello : public JsonSerializable
{     
    Q_OBJECT

public:
    static const QString HEARTBEAT_INTERVAL;

    Hello(QObject *parent = nullptr) : JsonSerializable(parent) {}
    Hello(const Hello &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    Hello(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Hello(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Hello(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    int getHeartbeatInterval();
    void setHeartbeatInterval(int interval);
    void setQJsonObject(const QJsonObject &jsonObject);

    Q_PROPERTY(int heartbeat_interval READ getHeartbeatInterval WRITE setHeartbeatInterval)
};
Q_DECLARE_METATYPE(Hello);
#endif // HELLO_H
