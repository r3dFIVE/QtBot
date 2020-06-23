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

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    QString
    getType() {
        return type;
    }

    void
    setType(QString type) {
        this->type = type;
    }

    int
    getAllow() {
        return allow;
    }

    void
    setAllow(int allow) {
        this->allow = allow;
    }

    int
    getDeny() {
        return deny;
    }

    void
    setDeny(int deny) {
        this->deny = deny;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(PermissionOverwrite)

#endif // PERMISSIONOVERWRITES_H
