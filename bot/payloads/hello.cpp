#include "hello.h"

#include "util/jsonutils.h"

QJsonValue
Hello::getHeartbeatInterval() {
    if (heartbeat_interval) {
        return QJsonValue(*heartbeat_interval);
    } else {
        return QJsonValue();
    }
}

void
Hello::setHeartbeatInterval(int interval) {
    heartbeat_interval = QSharedPointer<int>(new int(interval));;
}

void
Hello::setHeartbeatInterval(QJsonValue interval) {
    if (!interval.isNull()) {
        setHeartbeatInterval(interval.toInt());
    }
}

void
Hello::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}
void
Hello::write(QJsonObject &jsonObject)  {
    JsonUtils::writeToJson(*this, jsonObject);
}
