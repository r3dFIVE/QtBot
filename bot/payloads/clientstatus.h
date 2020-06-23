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

    QString
    getDesktop() {
        return desktop;
    }

    void
    setDesktop(QString desktop) {
        this->desktop = desktop;
    }

    QString
    getMobile() {
        return mobile;
    }

    void
    setMobile(QString mobile) {
        this->mobile = mobile;
    }

    QString
    getWeb() {
        return web;
    }

    void
    setWeb(QString web) {
        this->web = web;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(ClientStatus)

#endif // CLIENTSTATUS_H
