#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>

#include "src/jsonserializeable.h"


class GatewayPayload : public JsonSerializeable {
    Q_OBJECT
    Q_PROPERTY(QJsonObject _d READ d WRITE setD)
    Q_PROPERTY(int op READ op WRITE setOp)

    QJsonObject _d;
    QString _t;
    int _op = -1;
    int _s = -1;
 public:
    GatewayPayload(const GatewayPayload &payload) {}
    GatewayPayload() {}
    ~GatewayPayload() {}

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
