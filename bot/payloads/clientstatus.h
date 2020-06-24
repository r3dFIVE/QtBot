#ifndef CLIENTSTATUS_H
#define CLIENTSTATUS_H

#include "jsonserializable.h"


class ClientStatus : public JsonSerializable
{
    Q_OBJECT

public:
    const QString DESKTOP = "desktop";
    const QString MOBILE = "mobile";
    const QString WEB = "web";

    Q_PROPERTY(QString desktop READ getDesktop WRITE setDesktop)
    QString desktop;

    Q_PROPERTY(QString mobile READ getMobile WRITE setMobile)
    QString mobile;

    Q_PROPERTY(QString web READ getWeb WRITE setWeb)
    QString web;

    QString getDesktop();
    void setDesktop(QString desktop);
    QString getMobile();
    void setMobile(QString mobile);
    QString getWeb();
    void setWeb(QString web);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(ClientStatus)

#endif // CLIENTSTATUS_H
