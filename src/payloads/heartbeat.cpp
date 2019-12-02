#include "heartbeat.h"

int
Heartbeat::d() {
    return _d;
}

void
Heartbeat::setD(int d) {
    _d = d;
}

int
Heartbeat::op() {
    return _op;
}

void
Heartbeat::setOp(int op) {
    _op = op;
}

void
Heartbeat::read(const QJsonObject &jsonObject) {
    _d = jsonObject["d"].toInt();
    _op = jsonObject["op"].toInt();
}

void
Heartbeat::write(QJsonObject &jsonObject) const {
    jsonObject["d"] = _d;
    jsonObject["op"] = _op;
}
