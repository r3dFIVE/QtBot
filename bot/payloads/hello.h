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

    QJsonValue getHeartbeatInterval();
    void setHeartbeatInterval(int interval);
    void setHeartbeatInterval(QJsonValue interval);
    void read(const QJsonObject &jsonObject);
    void write(QJsonObject &jsonObject);
};
Q_DECLARE_METATYPE(Hello);
#endif // HEARTBEATINTERVAL_H
