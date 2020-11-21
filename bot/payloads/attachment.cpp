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

#include "attachment.h"

const QString Attachment::ID = "id";
const QString Attachment::FILENAME = "filename";
const QString Attachment::SIZE = "size";
const QString Attachment::URL = "url";
const QString Attachment::PROXY_URL = "proxy_url";
const QString Attachment::HEIGHT = "height";
const QString Attachment::WIDTH = "width";

QJsonValue
Attachment::getId() {
    return _jsonObject[ID];
}

void
Attachment::setId(QJsonValue id) {
    _jsonObject[ID] = id;
}

QJsonValue
Attachment::getFilename() {
    return _jsonObject[FILENAME];
}

void
Attachment::setFilename(QJsonValue filename) {
    _jsonObject[FILENAME] = filename;
}

QJsonValue
Attachment::getSize() {
    return _jsonObject[SIZE];
}

void
Attachment::setSize(QJsonValue size) {
    _jsonObject[SIZE] = size;
}

QJsonValue
Attachment::getUrl() {
    return _jsonObject[URL];
}

void
Attachment::setUrl(QJsonValue url) {
    _jsonObject[URL] = url;
}

QJsonValue
Attachment::getProxyUrl() {
    return _jsonObject[PROXY_URL];
}

void
Attachment::setProxyUrl(QJsonValue proxy_url) {
    _jsonObject[PROXY_URL] = proxy_url;
}

QJsonValue
Attachment::getHeight() {
    return _jsonObject[HEIGHT];
}

void
Attachment::setHeight(QJsonValue height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
Attachment::getWidth() {
    return _jsonObject[WIDTH];
}

void
Attachment::setWidth(QJsonValue width) {
    _jsonObject[WIDTH] = width;
}
