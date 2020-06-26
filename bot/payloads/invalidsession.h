#ifndef INVALIDSESSION_H
#define INVALIDSESSION_H

#include "jsonserializable.h"

#include <QObject>
#include <jsonutils.h>

class InvalidSession : public JsonSerializable
{
    Q_OBJECT
public:
    const QString D = "d";
    const QString OP = "op";

    int op;
    bool d;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

#endif // INVALIDSESSION_H
