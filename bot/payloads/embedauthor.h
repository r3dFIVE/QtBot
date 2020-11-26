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

#ifndef EMBEDAUTHOR_H
#define EMBEDAUTHOR_H

#include "jsonserializable.h"


class EmbedAuthor : public JsonSerializable
{
    Q_OBJECT

public:
    const static QString ICON_URL;
    const static QString NAME;
    const static QString PROXY_ICON_URL;
    const static QString URL;

    EmbedAuthor() {}
    EmbedAuthor(const QByteArray &json) : JsonSerializable(json) {}
    EmbedAuthor(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedAuthor(const QString &json) : JsonSerializable(json) {}

    QJsonValue getIconUrl() const;
    QJsonValue getName() const;
    QJsonValue getProxyIconUrl() const;
    QJsonValue getUrl() const;
    void setIconUrl(const QJsonValue &iconUrl);
    void setName(const QJsonValue &name);
    void setProxyIconUrl(const QJsonValue &proxyIconUrl);
    void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
};

Q_DECLARE_METATYPE(EmbedAuthor)

#endif // EMBEDAUTHOR_H
