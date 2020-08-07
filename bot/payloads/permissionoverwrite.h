#ifndef PERMISSIONOVERWRITES_H
#define PERMISSIONOVERWRITES_H

#include "jsonserializable.h"


class PermissionOverwrite : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString TYPE;
    static const QString ALLOW;
    static const QString DENY;

    PermissionOverwrite() {}
    PermissionOverwrite(const QByteArray &json) : JsonSerializable(json) {}
    PermissionOverwrite(const QJsonObject &json) : JsonSerializable(json) {}
    PermissionOverwrite(const QString &json) : JsonSerializable(json) {}

    QJsonValue getAllow() const;
    QJsonValue getDeny() const;
    QJsonValue getId() const;
    QJsonValue getType() const;
    void setAllow(const QJsonValue &allow);
    void setDeny(const QJsonValue &deny);
    void setId(const QJsonValue &id);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue allow READ getAllow WRITE setAllow)
    Q_PROPERTY(QJsonValue deny READ getDeny WRITE setDeny)
};

Q_DECLARE_METATYPE(PermissionOverwrite)

#endif // PERMISSIONOVERWRITES_H
