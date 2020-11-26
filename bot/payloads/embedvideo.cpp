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

#include "embedvideo.h"


const QString EmbedVideo::HEIGHT = "height";
const QString EmbedVideo::URL = "url";
const QString EmbedVideo::WIDTH = "width";

QJsonValue
EmbedVideo::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedVideo::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedVideo::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
EmbedVideo::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
EmbedVideo::getWidth() const {
    return _jsonObject[WIDTH];
}

void
EmbedVideo::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}
