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

#include "messageapplication.h"


const QString MessageApplication::TYPE = "type";
const QString MessageApplication::COVER_IMAGE = "cover_image";
const QString MessageApplication::DESCRIPTION = "description";
const QString MessageApplication::NAME = "name";
const QString MessageApplication::ICON = "icon";

QJsonValue
MessageApplication::getType() const {
    return _jsonObject[TYPE];
}

void
MessageApplication::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
MessageApplication::getCoverImage() const {
    return _jsonObject[COVER_IMAGE];
}

void
MessageApplication::setCoverImage(const QJsonValue &coverImage) {
    _jsonObject[COVER_IMAGE] = coverImage;
}

QJsonValue
MessageApplication::getDescription() const {
    return _jsonObject[DESCRIPTION];
}

void
MessageApplication::setDescription(const QJsonValue &description) {
    _jsonObject[DESCRIPTION] = description;
}

QJsonValue
MessageApplication::getIcon() const {
    return _jsonObject[ICON];
}

void
MessageApplication::setIcon(const QJsonValue &icon) {
    _jsonObject[ICON] = icon;
}

QJsonValue
MessageApplication::getName() const {
    return _jsonObject[NAME];
}

void
MessageApplication::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}
