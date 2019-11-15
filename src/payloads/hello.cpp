#include "hello.h"

void
Hello::read(const QJsonObject &jsonObject) {
    _heartbeatInterval = jsonObject["heartbeat_interval"].toInt();
}

void
Hello::write(QJsonObject &jsonObject) const {
     jsonObject["heartbeat_interval"] = _heartbeatInterval;
}

int
Hello::heartbeatInterval() {
    return _heartbeatInterval;
}

void
Hello::setHeartbeatInterval(int heartbeatInterval) {
    _heartbeatInterval = heartbeatInterval;
}
