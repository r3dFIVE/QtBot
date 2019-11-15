#ifndef HEARTBEATINTERVAL_H
#define HEARTBEATINTERVAL_H

#include <QString>

#include "src/jsonserializeable.h"

class Hello : public JsonSerializeable {
    int _heartbeatInterval;
public:
    int heartbeatInterval();
    void setHeartbeatInterval(int milliseconds);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // HEARTBEATINTERVAL_H
