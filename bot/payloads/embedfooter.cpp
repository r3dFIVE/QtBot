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

#include "embedfooter.h"


const QString EmbedFooter::ICON_URL = "icon_url";
const QString EmbedFooter::PROXY_ICON_URL = "proxy_icon_url";
const QString EmbedFooter::TEXT = "text";

QJsonValue
EmbedFooter::getText() const {
    return _jsonObject[TEXT];
}

void
EmbedFooter::setText(const QJsonValue &text) {
    _jsonObject[TEXT] = text;
}


QJsonValue
EmbedFooter::getIconUrl() const {
    return _jsonObject[ICON_URL];
}

void
EmbedFooter::setIconUrl(const QJsonValue &iconUrl) {
    _jsonObject[TEXT] = iconUrl;
}


QJsonValue
EmbedFooter::getProxyIconUrl() const {
    return _jsonObject[PROXY_ICON_URL];
}

void
EmbedFooter::setProxyIconUrl(const QJsonValue &proxyIconUrl) {
    _jsonObject[PROXY_ICON_URL] = proxyIconUrl;
}
