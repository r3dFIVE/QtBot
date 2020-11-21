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

#include "embed.h"


const QString Embed::TITLE = "title";
const QString Embed::TYPE = "type";
const QString Embed::DESCRIPTION = "description";
const QString Embed::URL = "url";
const QString Embed::TIMESTAMP = "timestamp";
const QString Embed::COLOR = "color";
const QString Embed::FOOTER = "footer";
const QString Embed::IMAGE = "image";
const QString Embed::THUMBNAIL = "thumbnail";
const QString Embed::VIDEO = "video";
const QString Embed::PROVIDER = "provider";
const QString Embed::AUTHOR = "author";
const QString Embed::FIELDS = "fields";

QJsonValue
Embed::getTitle() const {
    return _jsonObject[TITLE];
}

void
Embed::setTitle(const QJsonValue &title) {
    _jsonObject[TITLE] = title;
}

QJsonValue
Embed::getType() const {
    return _jsonObject[TYPE];
}

void
Embed::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
Embed::getDescription() const {
    return _jsonObject[DESCRIPTION];
}

void
Embed::setDescription(const QJsonValue &description) {
    _jsonObject[DESCRIPTION] = description;
}

QJsonValue
Embed::getUrl() const {
    return _jsonObject[URL];
}

void
Embed::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
Embed::getTimestamp() const {
    return _jsonObject[TIMESTAMP];
}

void
Embed::setTimestamp(const QJsonValue &timestamp) {
    _jsonObject[TIMESTAMP] = timestamp;
}

QJsonValue
Embed::getColor() const {
    return _jsonObject[COLOR];
}

void
Embed::setColor(const QJsonValue &color) {
    _jsonObject[COLOR] = color;
}

QJsonObject
Embed::getFooter() const {
    return _jsonObject[FOOTER].toObject();
}

void
Embed::setFooter(const QJsonObject &footer) {
    _jsonObject[FOOTER] = footer;
}

QJsonObject
Embed::getImage() const {
    return _jsonObject[IMAGE].toObject();
}

void
Embed::setImage(const QJsonObject &image) {
    _jsonObject[IMAGE] = image;
}

QJsonObject
Embed::getThumbnail() const {
    return _jsonObject[THUMBNAIL].toObject();
}

void
Embed::setThumbnail(const QJsonObject &thumbnail) {
    _jsonObject[THUMBNAIL] = thumbnail;
}

QJsonObject
Embed::getVideo() const {
    return _jsonObject[VIDEO].toObject();
}

void
Embed::setVideo(const QJsonObject &video) {
    _jsonObject[VIDEO] = video;
}

QJsonObject
Embed::getProvider() const {
    return _jsonObject[PROVIDER].toObject();
}

void
Embed::setProvider(const QJsonObject &provider) {
    _jsonObject[PROVIDER] = provider;
}

QJsonObject
Embed::getAuthor() const {
    return _jsonObject[AUTHOR].toObject();
}

void
Embed::setAuthor(const QJsonObject &author) {
    _jsonObject[AUTHOR] = author;
}


QJsonArray
Embed::getFields() const {    
    return _jsonObject[FIELDS].toArray();
}

void
Embed::setFields(const QJsonArray &fields) {
    _jsonObject[FIELDS] = fields;
}
