#include "gatewaypayload.h"

void
GatewayPayload::read(const QJsonObject &jsonObject) {
    d = jsonObject["d"].toObject();
    t = jsonObject["t"].toString();
    op = jsonObject["op"].toInt();
    s = jsonObject["s"].toInt();
}

void
GatewayPayload::write(QJsonObject &jsonObject) const {
    jsonObject["d"] = d;
    jsonObject["t"] = t;
    jsonObject["op"] = op;
    jsonObject["s"] = s;
}
