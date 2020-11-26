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

#include "embedimage.h"


const QString EmbedImage::HEIGHT = "height";
const QString EmbedImage::PROXY_URL = "proxy_url";
const QString EmbedImage::URL = "url";
const QString EmbedImage::WIDTH = "width";

QJsonValue
EmbedImage::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedImage::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedImage::getProxyUrl() const {
    return _jsonObject[PROXY_URL];
}

void
EmbedImage::setProxyUrl(const QJsonValue &proxyUrl) {
    _jsonObject[PROXY_URL] = proxyUrl;
}

QJsonValue
EmbedImage::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
EmbedImage::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
EmbedImage::getWidth() const {
    return _jsonObject[WIDTH];
}

void
EmbedImage::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}
