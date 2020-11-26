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

#ifndef EMBEDIMAGE_H
#define EMBEDIMAGE_H

#include "jsonserializable.h"


class EmbedImage : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString HEIGHT;
    static const QString PROXY_URL;
    static const QString URL;
    static const QString WIDTH;

    EmbedImage() {}
    EmbedImage(const QByteArray &json) : JsonSerializable(json) {}
    EmbedImage(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedImage(const QString &json) : JsonSerializable(json) {}

    QJsonValue getHeight() const;
    QJsonValue getProxyUrl() const;
    QJsonValue getUrl() const;
    QJsonValue getWidth() const;
    void setHeight(const QJsonValue &height);
    void setProxyUrl(const QJsonValue &proxyUrl);
    void setUrl(const QJsonValue &url);
    void setWidth(const QJsonValue &width);

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue proxy_url READ getProxyUrl WRITE setProxyUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(EmbedImage);

#endif // EMBEDIMAGE_H
