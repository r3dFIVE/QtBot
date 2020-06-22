#ifndef HELLO_H
#define HELLO_H

#include "heartbeat.h"
#include "jsonserializable.h"

#include <QSharedPointer>


class Hello : public JsonSerializable
{     
    Q_OBJECT
public:
    const QString HEARTBEAT_INTERVAL = "heartbeat_interval";

    Q_PROPERTY(QJsonValue heartbeat_interval READ getHeartbeatInterval WRITE setHeartbeatInterval)
    QSharedPointer<int> heartbeat_interval;

    QJsonValue
    getHeartbeatInterval() {
        if (heartbeat_interval) {
            return QJsonValue(*heartbeat_interval);
        } else {
            return QJsonValue();
        }
    }

    void
    setHeartbeatInterval(int interval) {
        heartbeat_interval = QSharedPointer<int>(new int(interval));;
    }

    void
    setHeartbeatInterval(QJsonValue interval) {
        if (!interval.isNull()) {
            setHeartbeatInterval(interval.toInt());
        }
    }

    void
    read(const QJsonObject &jsonObject) {
        JsonUtils::readFromJson(*this, jsonObject);
    }
    void
    write(QJsonObject &jsonObject)  {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};
Q_DECLARE_METATYPE(Hello);
#endif // HEARTBEATINTERVAL_H
