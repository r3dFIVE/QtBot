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

#include "activityparty.h"

const QString ActivityParty::ID = "id";
const QString ActivityParty::SIZE = "size";

QJsonValue
ActivityParty::getId() const {
    return _jsonObject[ID].toString();
}

void
ActivityParty::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonArray
ActivityParty::getSize() const {
    return _jsonObject[SIZE].toArray();
}

void
ActivityParty::setSize(const QJsonArray &size) {
    _jsonObject[SIZE] = size;
}

