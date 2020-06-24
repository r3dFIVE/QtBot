#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>

#include "jsonserializable.h"

class GatewayPayload : public JsonSerializable
{
    Q_OBJECT

public:
    const QString D = "d";
    const QString T = "t";
    const QString OP = "op";
    const QString S = "s";

    QJsonObject d;
    QString t;
    int op = -1;
    int s = -1;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(GatewayPayload)

#endif // GATEWAYPAYLOAD_H
