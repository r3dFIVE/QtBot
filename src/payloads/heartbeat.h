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
    Heartbeat(const Heartbeat &that) { Q_UNUSED(that) }
    ~Heartbeat() override {}
    void setD(int d);
    int d();
    void setOp(int op);
    int op();
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
private:
    int _op = GatewayOpcodes::HEARTBEAT;
    int _d = -1;
};
Q_DECLARE_METATYPE(Heartbeat);
#endif // HEARTBEART_H
