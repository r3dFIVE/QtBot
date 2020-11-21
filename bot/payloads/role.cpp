/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "role.h"


const QString Role::ID = "id";
const QString Role::NAME = "name";
const QString Role::COLOR = "color";
const QString Role::HOIST = "hoist";
const QString Role::POSITION = "position";
const QString Role::PERMISSIONS = "permissions";
const QString Role::MANAGED = "managed";
const QString Role::MENTIONABLE = "mentionable";

QJsonValue
Role::getId() const {
    return _jsonObject[ID];
}

void
Role::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
Role::getName() const {
    return _jsonObject[NAME];
}

void
Role::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
Role::getColor() const {
    return _jsonObject[COLOR];
}

void
Role::setColor(const QJsonValue &color) {
    _jsonObject[COLOR] = color;
}

QJsonValue
Role::getHoist() const {
    return _jsonObject[HOIST];
}

void
Role::setHoist(const QJsonValue &hoist) {
    _jsonObject[HOIST] = hoist;
}

QJsonValue
Role::getPosition() const {
    return _jsonObject[POSITION];
}

void
Role::setPosition(const QJsonValue &position) {
    _jsonObject[POSITION] = position;
}

QJsonValue
Role::getPermissions() const {
    return _jsonObject[PERMISSIONS];
}

void
Role::setPermissions(const QJsonValue &permissions) {
    _jsonObject[PERMISSIONS] = permissions;
}

QJsonValue
Role::getManaged() const {
    return _jsonObject[MANAGED];
}

void
Role::setManaged(const QJsonValue &managed) {
    _jsonObject[MANAGED] = managed;
}

QJsonValue
Role::getMentionable() const {
    return _jsonObject[MENTIONABLE];
}

void
Role::setMentionable(const QJsonValue &mentionable) {
    _jsonObject[MENTIONABLE] = mentionable;
}
