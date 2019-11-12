#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>

#include "src/jsonserializeable.h"


class GatewayPayload : public JsonSerializeable  {
    QString _d;
    QString _t;
    int _op;
    int _s;
 public:
    QString d();
    void setD(QString d);
    QString t();
    void setT(QString t);
    int op();
    void setOp(int op);
    int s();
    void setS(int s);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // GATEWAYPAYLOAD_H
