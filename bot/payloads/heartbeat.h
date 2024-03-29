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

#ifndef HEARTBEART_H
#define HEARTBEART_H

#include <QObject>

#include "util/gatewayevent.h"
#include "jsonserializable.h"

class Heartbeat : public JsonSerializable
{
    Q_OBJECT

public:    
    static const QString D;
    static const QString OP;

    Heartbeat(QObject *parent = nullptr) : JsonSerializable(parent) {
        setOp(GatewayEvent::HEARTBEAT);
    }
    Heartbeat(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {
        setOp(GatewayEvent::HEARTBEAT);
    }
    Heartbeat(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {
        setOp(GatewayEvent::HEARTBEAT);
    }
    Heartbeat(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {
        setOp(GatewayEvent::HEARTBEAT);
    }


    QJsonValue getD() const;
    QJsonValue getOp() const;
    void setD(const QJsonValue &d);
    void setOp(const QJsonValue &op);

    Q_PROPERTY(QJsonValue op READ getOp)
    Q_PROPERTY(QJsonValue d READ getD WRITE setD)
};

Q_DECLARE_METATYPE(Heartbeat)

#endif // HEARTBEART_H


