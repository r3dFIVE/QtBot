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

#include "embedprovider.h"


const QString EmbedProvider::NAME = "name";
const QString EmbedProvider::URL = "url";

QJsonValue
EmbedProvider::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedProvider::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedProvider::getName() const {
    return _jsonObject[NAME];
}

void
EmbedProvider::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}
