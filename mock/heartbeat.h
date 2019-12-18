#ifndef HEARTBEART_H
#define HEARTBEART_H

#include <QObject>

#include "jsonserializeable.h"
#include "globals.h"

class Heartbeat : public JsonSerializeable
{
    Q_OBJECT

public:
    Heartbeat() {}

    int d() {
        return _d;
    }

    void setD(int d) {
        _d = d;
    }

    int op() {
        return _op;
    }

    void setOp(int op) {
        _op = op;
    }

    void read(const QJsonObject &jsonObject) override {
        _d = jsonObject["d"].toInt();
        _op = jsonObject["op"].toInt();
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject["d"] = _d;
        jsonObject["op"] = _op;
    }

private:
    int _op = GatewayOpcodes::HEARTBEAT;
    int _d = -1;

};
Q_DECLARE_METATYPE(Heartbeat)
#endif // HEARTBEART_H
