#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>

#include "jsonserializeable.h"

class GatewayPayload : public JsonSerializeable
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

    void read(const QJsonObject &jsonObject) override {
        d = jsonObject[D].toObject();
        t = jsonObject[T].toString();
        op = jsonObject[OP].toInt();
        s = jsonObject[S].toInt();
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject[D] = d;
        jsonObject[T] = t;
        jsonObject[OP] = op;
        jsonObject[S] = s;
    }
};

Q_DECLARE_METATYPE(GatewayPayload)
#endif // GATEWAYPAYLOAD_H
