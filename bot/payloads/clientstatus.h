#ifndef CLIENTSTATUS_H
#define CLIENTSTATUS_H

#include "jsonserializable.h"


class ClientStatus : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString DESKTOP;
    static const QString MOBILE;
    static const QString WEB;

    ClientStatus() {}
    ClientStatus(const QByteArray &json) : JsonSerializable(json) {}
    ClientStatus(const QJsonObject &json) : JsonSerializable(json) {}
    ClientStatus(const QString &json) : JsonSerializable(json) {}

    QJsonValue getDesktop() const;
    QJsonValue getMobile() const;
    QJsonValue getWeb() const;
    void setDesktop(const QJsonValue &desktop);
    void setMobile(const QJsonValue &mobile);
    void setWeb(const QJsonValue &web);

    Q_PROPERTY(QJsonValue desktop READ getDesktop WRITE setDesktop)
    Q_PROPERTY(QJsonValue mobile READ getMobile WRITE setMobile)
    Q_PROPERTY(QJsonValue web READ getWeb WRITE setWeb)
};

Q_DECLARE_METATYPE(ClientStatus)

#endif // CLIENTSTATUS_H
