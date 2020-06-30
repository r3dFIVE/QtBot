#include "emoji.h"

#include <util/jsonutils.h>

QString
Emoji::getId() {
    return id;
}

void
Emoji::setId(QString id) {
    this->id = id;
}

QString
Emoji::getName() {
    return name;
}

void
Emoji::setName(QString name) {
    this->name = name;
}

QJsonArray
Emoji::getRoles() {
    QJsonArray roles;
    for (QString role : this->roles) {
        roles.push_back(role);
    }
    return roles;
}

void
Emoji::setRoles(QJsonArray roles) {
    for (QJsonValue roleId : roles) {
        this->roles.push_back(roleId.toString());
    }
}

QJsonObject
Emoji::getUser() {
    if (user) {
        return (user->toQJsonObject());
    } else {
        return QJsonObject();
    }
}

void
Emoji::setUser(QJsonObject user) {
    if (!user.isEmpty()) {
        this->user = QSharedPointer<User>(new User);
        JsonUtils::readFromJson(*this->user, user);
    }
}

QJsonValue
Emoji::getRequireColons() {
    if (require_colons) {
        return QJsonValue(*require_colons);
    } else {
        return QJsonValue();
    }
}

void
Emoji::setRequireColons(QJsonValue require_colons) {
    if (!require_colons.isNull()) {
        this->require_colons = QSharedPointer<bool>(new bool(require_colons.toBool()));
    }
}

QJsonValue
Emoji::getManaged() {
    if (managed) {
        return QJsonValue(*managed);
    } else {
        return QJsonValue();
    }
}

void
Emoji::setManaged(QJsonValue managed) {
    if (!managed.isNull()) {
        this->managed = QSharedPointer<bool>(new bool(managed.toBool()));
    }
}

QJsonValue
Emoji::getAnimated() {
    if (animated) {
        return QJsonValue(*animated);
    } else {
        return QJsonValue();
    }
}

void
Emoji::setAnimated(QJsonValue animated) {
    if (!animated.isNull()) {
        this->animated = QSharedPointer<bool>(new bool(animated.toBool()));
    }
}

QJsonValue
Emoji::getAvailable() {
    if (require_colons) {
        return QJsonValue(*require_colons);
    } else {
        return QJsonValue();
    }
}

void
Emoji::setAvailable(QJsonValue available) {
    if (!available.isNull()) {
        this->available = QSharedPointer<bool>(new bool(available.toBool()));
    }
}

void
Emoji::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
Emoji::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
