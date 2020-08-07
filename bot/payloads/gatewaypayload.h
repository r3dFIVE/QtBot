#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include "jsonserializable.h"


class GatewayPayload : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString D;
    static const QString OP;
    static const QString S;
    static const QString T;

    GatewayPayload() {}
    GatewayPayload(const QJsonObject &json) : JsonSerializable(json) {}
    GatewayPayload(const QString &json) : JsonSerializable(json) {}

    QJsonObject getD() const;
    QJsonValue getV() const;
    QJsonValue getOp() const;
    QJsonValue getS() const;
    QJsonValue getT() const;
    void setD(const QJsonValue &getD);
    void setOp(const QJsonValue &getOp);
    void setS(const QJsonValue &getS);
    void setT(const QJsonValue &getT);
};

Q_DECLARE_METATYPE(GatewayPayload)

#endif // GATEWAYPAYLOAD_H
