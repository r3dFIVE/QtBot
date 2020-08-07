#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "jsonserializable.h"


class IdentifyProperties : public JsonSerializable
{    
    QString $os = QSysInfo::productType();
    QString $browser = "QtBot";
    QString $device = "QtBot";

public:
    static const QString OS;
    static const QString BROWSER;
    static const QString DEVICE;

    IdentifyProperties();
    IdentifyProperties(const QByteArray &json) : JsonSerializable(json) {}
    IdentifyProperties(const QJsonObject &json) : JsonSerializable(json) {}
    IdentifyProperties(const QString &json) : JsonSerializable(json) {}

    QJsonValue getOS() const;
    QJsonValue getBrowser() const;
    QJsonValue getDevice() const;
    void setBrowser(const QJsonValue &browser);
    void setDevice(const QJsonValue &device);
    void setOS(const QJsonValue &os);

    Q_PROPERTY(QJsonValue browser READ getBrowser WRITE setBrowser)
    Q_PROPERTY(QJsonValue device READ getDevice WRITE setDevice)
    Q_PROPERTY(QJsonValue os READ getOS WRITE setOS)
};

#endif // PROPERTIES_H
