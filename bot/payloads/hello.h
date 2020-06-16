#ifndef HEARTBEATINTERVAL_H
#define HEARTBEATINTERVAL_H

#include "jsonserializeable.h"

class Hello : public JsonSerializeable
{
public:
    int heartbeatInterval;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // HEARTBEATINTERVAL_H
