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

#include "embedauthor.h"

const QString EmbedAuthor::ICON_URL = "icon_url";
const QString EmbedAuthor::NAME = "name";
const QString EmbedAuthor::PROXY_ICON_URL = "proxy_icon_url";
const QString EmbedAuthor::URL = "url";


EmbedAuthor::EmbedAuthor(const QString &name,
                         const QString &url,
                         const QString &iconUrl,
                         QObject *parent) : JsonSerializable(parent) {
    _jsonObject[NAME] = name;

    _jsonObject[URL] = url;

    _jsonObject[ICON_URL] = iconUrl;
}

QJsonValue
EmbedAuthor::getName() const {
    return _jsonObject[NAME];
}

void
EmbedAuthor::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
EmbedAuthor::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedAuthor::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedAuthor::getIconUrl() const {
    return _jsonObject[ICON_URL];
}

void
EmbedAuthor::setIconUrl(const QJsonValue &iconUrl) {
    _jsonObject[ICON_URL] = iconUrl;
}

QJsonValue
EmbedAuthor::getProxyIconUrl() const {
    return _jsonObject[PROXY_ICON_URL];
}

void
EmbedAuthor::setProxyIconUrl(const QJsonValue &proxyIconUrl) {
    _jsonObject[PROXY_ICON_URL] = proxyIconUrl;
}
