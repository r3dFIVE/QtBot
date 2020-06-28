#ifndef HEARTBEART_H
#define HEARTBEART_H

#include <QObject>

#include "jsonserializable.h"
#include "globals.h"

class Heartbeat : public JsonSerializable
{
    Q_OBJECT

public:
    const QString D = "d";
    const QString OP = "op";

    Q_PROPERTY(int op READ getOp)
    int op = GatewayEvents::HEARTBEAT;

    Q_PROPERTY(int d READ getD WRITE setD)
    int d = -1;

    int getD();
    void setD(int value);
    int getOp();
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(Heartbeat)

#endif // HEARTBEART_H


