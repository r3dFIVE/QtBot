#include "heartbeat.h"


const QString Heartbeat::D = "d";
const QString Heartbeat::OP = "op";

QJsonValue
Heartbeat::getD() const {
    return _jsonObject[D].toInt();
}

void
Heartbeat::setD(const QJsonValue &d) {
    _jsonObject[D] = d;
}

QJsonValue
Heartbeat::getOp() const {
    return  _jsonObject[OP];
}

void
Heartbeat::setOp(const QJsonValue &event) {
    _jsonObject[OP] = event;
}

