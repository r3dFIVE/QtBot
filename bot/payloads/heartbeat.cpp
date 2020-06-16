#include "heartbeat.h"

void
Heartbeat::read(const QJsonObject &jsonObject) {
    d = jsonObject[D].toInt();
    op = jsonObject[OP].toInt();
}

void
Heartbeat::write(QJsonObject &jsonObject) const {
    if (d == -1) {
        jsonObject[D] = QJsonValue::Null;
    } else {
        jsonObject[D] = d;
    }
    jsonObject[OP] = op;
}
