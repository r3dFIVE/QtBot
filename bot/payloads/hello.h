#ifndef HELLO_H
#define HELLO_H

#include "jsonserializable.h"


class Hello : public JsonSerializable
{     
    Q_OBJECT

public:
    static const QString HEARTBEAT_INTERVAL;

    Hello() {}
    Hello(const QByteArray &json) : JsonSerializable(json) {}
    Hello(const QJsonObject &json) : JsonSerializable(json) {}
    Hello(const QString &json) : JsonSerializable(json) {}

    int getHeartbeatInterval();
    void setHeartbeatInterval(int interval);
    void setQJsonObject(const QJsonObject &jsonObject);

    Q_PROPERTY(int heartbeat_interval READ getHeartbeatInterval WRITE setHeartbeatInterval)
};
Q_DECLARE_METATYPE(Hello);
#endif // HELLO_H
