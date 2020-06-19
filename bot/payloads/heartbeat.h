#ifndef HEARTBEART_H
#define HEARTBEART_H

#include <QObject>

#include "jsonserializeable.h"
#include "globals.h"

class Heartbeat : public JsonSerializeable
{
    Q_OBJECT

public:
    const QString D = "d";
    const QString OP = "op";

    Q_PROPERTY(int op READ getOp)
    int op = GatewayOpcodes::HEARTBEAT;

    Q_PROPERTY(int d READ getD WRITE setD)
    int d = -1;

    int
    getD() const {
        return d;
    }

    void
    setD(int value) {
        d = value;
    }

    int
    getOp() const {
        return op;
    }

    void
    read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void
    write(QJsonObject &jsonObject) override {
        if (d == -1) {
            jsonObject[D] = QJsonValue::Null;
        } else {
            jsonObject[D] = d;
        }
        jsonObject[OP] = op;
    }
};

Q_DECLARE_METATYPE(Heartbeat)

#endif // HEARTBEART_H


