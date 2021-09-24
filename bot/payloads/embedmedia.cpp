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

#include "embedmedia.h"


const QString EmbedMedia::HEIGHT = "height";
const QString EmbedMedia::PROXY_URL = "proxy_url";
const QString EmbedMedia::URL = "url";
const QString EmbedMedia::WIDTH = "width";

EmbedMedia::EmbedMedia(const QString &url, const int height, const int width) {
    _jsonObject[URL] = url;

    if (height > 0) {
        _jsonObject[HEIGHT] = height;
    }

    if (width > 0) {
        _jsonObject[WIDTH] = width;
    }
}

QJsonValue
EmbedMedia::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedMedia::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedMedia::getProxyUrl() const {
    return _jsonObject[PROXY_URL];
}

void
EmbedMedia::setProxyUrl(const QJsonValue &proxyUrl) {
    _jsonObject[PROXY_URL] = proxyUrl;
}

QJsonValue
EmbedMedia::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
EmbedMedia::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
EmbedMedia::getWidth() const {
    return _jsonObject[WIDTH];
}

void
EmbedMedia::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}
