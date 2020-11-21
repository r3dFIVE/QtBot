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

#include "embedfield.h"

const QString EmbedField::INLINE = "inline";
const QString EmbedField::NAME = "name";
const QString EmbedField::VALUE = "value";

QJsonValue
EmbedField::getValue() const {
    return _jsonObject[VALUE];
}

void
EmbedField::setValue(const QJsonValue &value) {
    _jsonObject[VALUE] = value;
}

QJsonValue
EmbedField::getInline() const {
    return _jsonObject[INLINE];
}

void
EmbedField::setInline(const QJsonValue &inln) {
    _jsonObject[INLINE] = inln;
}

QJsonValue
EmbedField::getName() const {
    return _jsonObject[NAME];
}

void EmbedField::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}
