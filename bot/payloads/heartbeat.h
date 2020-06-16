#ifndef HEARTBEART_H
#define HEARTBEART_H

#include <QObject>

#include "jsonserializeable.h"
#include "globals.h"

class Heartbeat : public JsonSerializeable
{
    const QString D = "d";
    const QString OP = "op";
public:
    int op = GatewayOpcodes::HEARTBEAT;
    int d = -1;

    void read(const QJsonObject &jsonObject) override {
        d = jsonObject[D].toInt();
        op = jsonObject[OP].toInt();
    }

    void write(QJsonObject &jsonObject) const override {
        if (d == -1) {
            jsonObject[D] = QJsonValue::Null;
        } else {
            jsonObject[D] = d;
        }
        jsonObject[OP] = op;
    }
};

#endif // HEARTBEART_H
