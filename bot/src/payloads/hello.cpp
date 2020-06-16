#include "hello.h"

void
Hello::read(const QJsonObject &jsonObject) {
    heartbeatInterval = jsonObject["heartbeat_interval"].toInt();
}

void
Hello::write(QJsonObject &jsonObject) const {
    jsonObject["heartbeat_interval"] = heartbeatInterval;
}
