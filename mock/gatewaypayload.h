#ifndef GATEWAYPAYLOAD_H
#define GATEWAYPAYLOAD_H

#include <QString>
#include <QObject>
#include <QJsonDocument>

#include "jsonserializeable.h"

class GatewayPayload : public JsonSerializeable {
    Q_OBJECT

public:
   GatewayPayload(const GatewayPayload &payload) { Q_UNUSED(payload) }
   GatewayPayload() {}
   ~GatewayPayload() override {}

   QJsonObject d() {
       return _d;
   }

   void setD(QJsonObject d) {
       _d = d;
   }


   QString t() {
       return _t;
   }

   void setT(QString t) {
       _t = t;
   }

   int op() {
       return _op;
   }

   void setOp(int op) {
       _op = op;
   }

   int s() {
       return _s;
   }

   void setS(int s) {
       _s = s;
   }

   void read(const QJsonObject &jsonObject) override {
       _d = jsonObject["d"].toObject();
       _t = jsonObject["t"].toString();
       _op = jsonObject["op"].toInt();
       _s = jsonObject["s"].toInt();
   }

   void write(QJsonObject &jsonObject) const override {
       jsonObject["d"] = _d;
       jsonObject["t"] = _t;
       jsonObject["op"] = _op;
       jsonObject["s"] = _s;
   }

private:
    QJsonObject _d;
    QString _t;
    int _op = -1;
    int _s = -1;
};
Q_DECLARE_METATYPE(GatewayPayload)
#endif // GATEWAYPAYLOAD_H
