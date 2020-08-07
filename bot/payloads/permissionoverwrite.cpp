#include "permissionoverwrite.h"


const QString PermissionOverwrite::ID = "id";
const QString PermissionOverwrite::TYPE = "type";
const QString PermissionOverwrite::ALLOW = "allow";
const QString PermissionOverwrite::DENY = "deny";

QJsonValue
PermissionOverwrite::getId() const {
    return _jsonObject[ID];
}

void
PermissionOverwrite::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
PermissionOverwrite::getType() const {
    return _jsonObject[TYPE];
}

void
PermissionOverwrite::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
PermissionOverwrite::getAllow() const {
    return _jsonObject[ALLOW];
}

void
PermissionOverwrite::setAllow(const QJsonValue &allow) {
    _jsonObject[ALLOW] = allow;
}

QJsonValue
PermissionOverwrite::getDeny() const {
    return _jsonObject[DENY];
}

void
PermissionOverwrite::setDeny(const QJsonValue &deny) {
    _jsonObject[DENY] = deny;
}
