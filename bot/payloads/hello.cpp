#include "hello.h"


const QString Hello::HEARTBEAT_INTERVAL = "heartbeat_interval";

int
Hello::getHeartbeatInterval() {
    return _jsonObject[HEARTBEAT_INTERVAL].toInt();
}

void
Hello::setHeartbeatInterval(int interval) {
    _jsonObject[HEARTBEAT_INTERVAL] = interval;
}
