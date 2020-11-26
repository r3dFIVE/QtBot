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

#include "gatewaypayload.h"


const QString GatewayPayload::D = "d";
const QString GatewayPayload::T = "t";
const QString GatewayPayload::OP = "op";
const QString GatewayPayload::S = "s";

QJsonObject
GatewayPayload::getD() const {
    return _jsonObject[D].toObject();
}

QJsonValue
GatewayPayload::getV() const {
    return _jsonObject[D];
}

QJsonValue
GatewayPayload::getOp() const {
    return _jsonObject[OP];
}

QJsonValue
GatewayPayload::getS() const {
    return _jsonObject[S];
}

QJsonValue
GatewayPayload::getT() const {
    return _jsonObject[T];
}

void GatewayPayload::setD(const QJsonValue &d) {
    _jsonObject[D] = d;
}

void GatewayPayload::setOp(const QJsonValue &op) {
    _jsonObject[OP] = op;
}

void GatewayPayload::setS(const QJsonValue &s) {
    _jsonObject[S] = s;
}

void GatewayPayload::setT(const QJsonValue &t) {
    _jsonObject[T] = t;
}
