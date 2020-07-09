#include "role.h"

#include "util/serializationutils.h"

QString
Role::getId() {
    return id;
}

void
Role::setId(QString id) {
    this->id = id;
}

QString
Role::getName() {
    return name;
}

void
Role::setName(QString name) {
    this->name = name;
}

int
Role::getColor() {
    return color;
}

void
Role::setColor(int color) {
    this->color = color;
}

bool
Role::getHoist() {
    return hoist;
}

void
Role::setHoist(bool hoist) {
    this->hoist = hoist;
}

int
Role::getPosition() {
    return position;
}

void
Role::setPosition(int position) {
    this->position = position;
}

int
Role::getPermissions() {
    return permissions;
}

void
Role::setPermissions(int permissions) {
    this->permissions = permissions;
}

bool
Role::getManaged() {
    return managed;
}

void
Role::setManaged(bool managed) {
    this->managed = managed;
}

bool
Role::getMentionable() {
    return mentionable;
}

void
Role::setMentionable(bool mentionable) {
    this->mentionable = mentionable;
}

void
Role::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Role::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
