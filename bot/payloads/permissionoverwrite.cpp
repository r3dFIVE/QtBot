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
