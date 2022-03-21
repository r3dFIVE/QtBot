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
const QString Embed::AUTHOR = "author";
const QString Embed::FIELDS = "fields";

const int Embed::DECRIPTION_MAX_LENGTH = 4000;
const int Embed::DECRIPTION_SHORT_MAX_LENGTH = 200;
const int Embed::TITLE_MAX_LENGTH = 200;
const int Embed::TOTAL_MAX_LENGTH = 6000;
const int Embed::FIELDS_MAX = 25;
const int Embed::FIELDS_VALUE_MAX_LENGTH = 1024;
const int Embed::FOOTER_TEXT_MAX_LENGTH = 2000;
const int Embed::AUTHOR_NAME_MAX_LENGTH = 200;

Embed::Embed(const QString &title,
             const QString &description,
             const QString &url,
             const int color,
             QObject *parent) :JsonSerializable(parent) {
    _jsonObject[TITLE] = title;

    _jsonObject[DESCRIPTION] = description;

    _jsonObject[URL] = url;

    _jsonObject[COLOR] = color;
}

Embed&
Embed::operator=(const Embed &other) {
    if (this == &other) {
        return *this;
    }

    _jsonObject = other._jsonObject;

    return *this;
}

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

void
Embed::addField(EmbedField *field) {
    QJsonArray array = _jsonObject[FIELDS].toArray();

    array << field->object();

    _jsonObject[FIELDS] = array;
}

void
Embed::addField(const QJsonObject &field) {
    QJsonArray array = _jsonObject[FIELDS].toArray();

    array << field;

    _jsonObject[FIELDS] = array;
}

void
Embed::setAuthor(EmbedAuthor *author) {
    _jsonObject[AUTHOR] = author->object();
}

void
Embed::setFooter(EmbedFooter *footer) {
    _jsonObject[FOOTER] = footer->object();
}

void
Embed::setImage(EmbedMedia *image) {
    _jsonObject[IMAGE] = image->object();
}

void
Embed::setThumbnail(EmbedMedia *thumbnail) {
    _jsonObject[THUMBNAIL] = thumbnail->object();
}

void
Embed::setVideo(EmbedMedia *video) {
    _jsonObject[VIDEO] = video->object();
}
