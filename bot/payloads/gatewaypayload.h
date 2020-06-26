#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>

#include "jsonserializable.h"

namespace GatewayPayload {

static const QString D = "d";
static const QString T = "t";
static const QString OP = "op";
static const QString S = "s";
static const QString VALUE = "value";

class GatewayPayload : public JsonSerializable
{
    Q_OBJECT

public:

    int op = -1;
    QJsonObject d;    
    int s= -1;
    QString t;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};
}

Q_DECLARE_METATYPE(GatewayPayload::GatewayPayload)

#endif // GATEWAYPAYLOAD_H
