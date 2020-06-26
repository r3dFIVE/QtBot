#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "jsonserializable.h"


class IdentifyProperties : public JsonSerializable
{
public:
    const QString OS = "$os";
    const QString BROWSER = "$browser";
    const QString DEVICE = "$device";

    QString $os = QSysInfo::productType();
    QString $browser = "QtBot";
    QString $device = "QtBot";

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

#endif // PROPERTIES_H