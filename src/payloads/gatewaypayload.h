#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>
#include <QJsonDocument>

#include "src/jsonserializeable.h"


class GatewayPayload : public JsonSerializeable {
    Q_OBJECT

    QJsonObject _d;
    QString _t;
    int _op = -1;
    int _s = -1;
 public:
    GatewayPayload(const GatewayPayload &payload) { Q_UNUSED(payload) }
    GatewayPayload() {}
    ~GatewayPayload() override {}

    QJsonObject d();
    void setD(QJsonObject d);
    QString t();
    void setT(QString t);
    int op();
    void setOp(int op);
    int s();
    void setS(int s);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};
Q_DECLARE_METATYPE(GatewayPayload)
#endif // GATEWAYPAYLOAD_H
