/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "emoji.h"


const QString Emoji::ID = "id";
const QString Emoji::NAME = "name";
const QString Emoji::ROLES = "roles";
const QString Emoji::USER = "user";
const QString Emoji::REQUIRE_COLONS = "require_colons";
const QString Emoji::MANAGED = "managed";
const QString Emoji::ANIMATED = "animated";
const QString Emoji::AVAILABLE = "available";

QJsonValue
Emoji::getId() const {
    return _jsonObject[ID];
}

void
Emoji::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
Emoji::getName() const {
    return _jsonObject[NAME];
}

void
Emoji::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonArray
Emoji::getRoles() const {
    return _jsonObject[ROLES].toArray();
}

void
Emoji::setRoles(const QJsonArray &roles) {
    _jsonObject[ROLES] = roles;
}

QJsonObject
Emoji::getUser() const {
    return _jsonObject[USER].toObject();
}

void
Emoji::setUser(const QJsonObject &user) {
    _jsonObject[USER] = user;
}

QJsonValue
Emoji::getRequireColons() const {
    return _jsonObject[REQUIRE_COLONS];
}

void
Emoji::setRequireColons(const QJsonValue &requireColons) {
    _jsonObject[REQUIRE_COLONS] = requireColons;
}

QJsonValue
Emoji::getManaged() const {
    return _jsonObject[MANAGED];
}

void
Emoji::setManaged(const QJsonValue &managed) {
    _jsonObject[MANAGED] = managed;
}

QJsonValue
Emoji::getAnimated() const {
    return _jsonObject[ANIMATED];
}

void
Emoji::setAnimated(const QJsonValue &animated) {
    _jsonObject[ANIMATED] = animated;
}

QJsonValue
Emoji::getAvailable() const {
    return _jsonObject[AVAILABLE];
}

void
Emoji::setAvailable(const QJsonValue &available) {
    _jsonObject[AVAILABLE] = available;
}
