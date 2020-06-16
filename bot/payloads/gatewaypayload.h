#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>

#include "jsonserializeable.h"

class GatewayPayload : public JsonSerializeable
{
    Q_OBJECT

public:
    QJsonObject d;
    QString t;
    int op = -1;
    int s = -1;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};
Q_DECLARE_METATYPE(GatewayPayload)
#endif // GATEWAYPAYLOAD_H
