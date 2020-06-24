#include "permissionoverwrite.h"

#include <jsonutils.h>

QString
PermissionOverwrite::getId() {
    return id;
}

void
PermissionOverwrite::setId(QString id) {
    this->id = id;
}

QString
PermissionOverwrite::getType() {
    return type;
}

void
PermissionOverwrite::setType(QString type) {
    this->type = type;
}

int
PermissionOverwrite::getAllow() {
    return allow;
}

void
PermissionOverwrite::setAllow(int allow) {
    this->allow = allow;
}

int
PermissionOverwrite::getDeny() {
    return deny;
}

void
PermissionOverwrite::setDeny(int deny) {
    this->deny = deny;
}

void
PermissionOverwrite::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
PermissionOverwrite::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
