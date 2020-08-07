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
