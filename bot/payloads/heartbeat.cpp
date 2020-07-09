#include "heartbeat.h"

#include <util/serializationutils.h>

int
Heartbeat::getD() {
    return d;
}

void
Heartbeat::setD(int value) {
    d = value;
}

int
Heartbeat::getOp() {
    return op;
}

void
Heartbeat::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Heartbeat::write(QJsonObject &jsonObject) {
    if (d == -1) {
        jsonObject[D] = QJsonValue::Null;
    } else {
        jsonObject[D] = d;
    }
    jsonObject[OP] = op;
}
