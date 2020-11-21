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

#include "activityemoji.h"

const QString ActivityEmoji::NAME = "name";
const QString ActivityEmoji::ID = "id";
const QString ActivityEmoji::ANIMATED = "animated";

QJsonValue
ActivityEmoji::getName() const {
    return _jsonObject[NAME];
}

void
ActivityEmoji::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
ActivityEmoji::getId() const {
    return _jsonObject[ID];
}

void
ActivityEmoji::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
ActivityEmoji::getAnimated() const {
    return _jsonObject[ANIMATED];
}

void
ActivityEmoji::setAnimated(const QJsonValue &animated) {
    _jsonObject[ANIMATED] = animated;
}
