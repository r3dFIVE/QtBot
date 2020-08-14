#ifndef HEARTBEART_H
#define HEARTBEART_H

#include <QObject>

#include "jsonserializable.h"
#include "util/globals.h"

class Heartbeat : public JsonSerializable
{
    Q_OBJECT

public:    
    static const QString D;
    static const QString OP;

    Heartbeat() { setOp(GatewayEvent::HEARTBEAT); }
    Heartbeat(const QJsonObject &json) : JsonSerializable(json) { setOp(GatewayEvent::HEARTBEAT); }
    Heartbeat(const QString &json) : JsonSerializable(json) { setOp(GatewayEvent::HEARTBEAT); }
    Heartbeat(const QByteArray &json) : JsonSerializable(json) { setOp(GatewayEvent::HEARTBEAT); }


    QJsonValue getD() const;
    QJsonValue getOp() const;
    void setD(const QJsonValue &d);
    void setOp(const QJsonValue &op);

    Q_PROPERTY(QJsonValue op READ getOp)
    Q_PROPERTY(QJsonValue d READ getD WRITE setD)
};

Q_DECLARE_METATYPE(Heartbeat)

#endif // HEARTBEART_H


