#include "gatewaypayload.h"

QJsonObject
GatewayPayload::d() {
    return _d;
}

void
GatewayPayload::setD(QJsonObject d) {
    _d = d;
}


QString
GatewayPayload::t() {
    return _t;
}

void
GatewayPayload::setT(QString t) {
    _t = t;
}

int
GatewayPayload::op() {
    return _op;
}

void
GatewayPayload::setOp(int op) {
    _op = op;
}

int
GatewayPayload::s() {
    return _s;
}

void
GatewayPayload::setS(int s) {
    _s = s;
}


void
GatewayPayload::read(const QJsonObject &jsonObject) {
    _d = jsonObject["d"].toObject();
    _t = jsonObject["t"].toString();
    _op = jsonObject["op"].toInt();
    _s = jsonObject["s"].toInt();
}

void
GatewayPayload::write(QJsonObject &jsonObject) const {
    jsonObject["d"] = _d;
    jsonObject["t"] = _t;
    jsonObject["op"] = _op;
    jsonObject["s"] = _s;
}
