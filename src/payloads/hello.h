#ifndef HEARTBEATINTERVAL_H
#define HEARTBEATINTERVAL_H

#include "src/jsonserializeable.h"

class Hello : public JsonSerializeable {
    int _heartbeatInterval;

public:
    int heartbeatInterval()  {
        return _heartbeatInterval;
    }

    void setHeartbeatInterval(int heartbeatInterval) {
        _heartbeatInterval = heartbeatInterval;
    }

    void read(const QJsonObject &jsonObject) override {
        _heartbeatInterval = jsonObject["heartbeat_interval"].toInt();
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject["heartbeat_interval"] = _heartbeatInterval;
   }
};

#endif // HEARTBEATINTERVAL_H
