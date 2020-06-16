#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "jsonserializeable.h"


class Properties : public JsonSerializeable
{
    const QString OS = "$os";
    const QString BROWSER = "$browser";
    const QString DEVICE = "$device";
public:
    QString $os = QSysInfo::productType();
    QString $browser = "QtBot";
    QString $device = "QtBot";

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // PROPERTIES_H
