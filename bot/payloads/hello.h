#ifndef HELLO_H
#define HELLO_H

#include "jsonserializeable.h"

class Hello : public JsonSerializeable
{     
public:
    const QString HEARTBEAT_INTERVAL = "heartbeat_interval";

    int heartbeatInterval;

    void read(const QJsonObject &jsonObject) override {
        heartbeatInterval = jsonObject[HEARTBEAT_INTERVAL].toInt();
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject[HEARTBEAT_INTERVAL] = heartbeatInterval;
    }
};

#endif // HEARTBEATINTERVAL_H
