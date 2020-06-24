#ifndef PERMISSIONOVERWRITES_H
#define PERMISSIONOVERWRITES_H

#include "jsonserializable.h"


class PermissionOverwrite : public JsonSerializable
{
    Q_OBJECT

public:
    const QString ID = "id";
    const QString TYPE = "type";
    const QString ALLOW = "allow";
    const QString DENY = "deny";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QString type READ getType WRITE setType)
    QString type;

    Q_PROPERTY(int allow READ getAllow WRITE setAllow)
    int allow;

    Q_PROPERTY(int deny READ getDeny WRITE setDeny)
    int deny;

    QString getId();
    void setId(QString id);
    QString getType();
    void setType(QString type);
    int getAllow();
    void setAllow(int allow);
    int getDeny();
    void setDeny(int deny);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(PermissionOverwrite)

#endif // PERMISSIONOVERWRITES_H
