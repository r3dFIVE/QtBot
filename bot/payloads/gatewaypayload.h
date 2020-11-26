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

#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include "jsonserializable.h"


class GatewayPayload : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString D;
    static const QString OP;
    static const QString S;
    static const QString T;

    GatewayPayload() {}
    GatewayPayload(const QJsonObject &json) : JsonSerializable(json) {}
    GatewayPayload(const QString &json) : JsonSerializable(json) {}

    QJsonObject getD() const;
    QJsonValue getV() const;
    QJsonValue getOp() const;
    QJsonValue getS() const;
    QJsonValue getT() const;
    void setD(const QJsonValue &getD);
    void setOp(const QJsonValue &getOp);
    void setS(const QJsonValue &getS);
    void setT(const QJsonValue &getT);
};

Q_DECLARE_METATYPE(GatewayPayload)

#endif // GATEWAYPAYLOAD_H
