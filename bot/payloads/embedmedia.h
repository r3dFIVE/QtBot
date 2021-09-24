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

#ifndef EMBEDMEDIA_H
#define EMBEDMEDIA_H

#include "jsonserializable.h"


class EmbedMedia : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString HEIGHT;
    static const QString PROXY_URL;
    static const QString URL;
    static const QString WIDTH;

    EmbedMedia() {}
    EmbedMedia(const QString &url, const int height, const int width);
    EmbedMedia(const QByteArray &json) : JsonSerializable(json) {}
    EmbedMedia(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedMedia(const QString &json) : JsonSerializable(json) {}

    Q_INVOKABLE QJsonValue getHeight() const;
    Q_INVOKABLE QJsonValue getProxyUrl() const;
    Q_INVOKABLE QJsonValue getUrl() const;
    Q_INVOKABLE QJsonValue getWidth() const;
    Q_INVOKABLE void setHeight(const QJsonValue &height);
    Q_INVOKABLE void setProxyUrl(const QJsonValue &proxyUrl);
    Q_INVOKABLE void setUrl(const QJsonValue &url);
    Q_INVOKABLE void setWidth(const QJsonValue &width);

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(EmbedMedia);

#endif // EMBEDMEDIA_H
