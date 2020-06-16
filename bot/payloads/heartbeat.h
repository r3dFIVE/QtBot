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

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};
#endif // HEARTBEART_H
