#include "gatewaypayload.h"

namespace GatewayPayload {
void
GatewayPayload::read(const QJsonObject &jsonObject) {
    if (jsonObject[D].isObject()) {
        d = jsonObject[D].toObject();
    } else {
        QJsonObject o;
        o.insert(VALUE, jsonObject[D]);
        d = o;
    }

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
}
