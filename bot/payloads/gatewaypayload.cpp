#include "gatewaypayload.h"

void
GatewayPayload::read(const QJsonObject &jsonObject) {
    d = jsonObject[D].toObject();
    t = jsonObject[T].toString();
    op = jsonObject[OP].toInt();
    s = jsonObject[S].toInt();
}

void
GatewayPayload::write(QJsonObject &jsonObject) {
    jsonObject[D] = d;
    jsonObject[T] = t;
    jsonObject[OP] = op;
    jsonObject[S] = s;
}
