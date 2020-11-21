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

#ifndef EMBEDVIDEO_H
#define EMBEDVIDEO_H

#include "jsonserializable.h"


class EmbedVideo : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString HEIGHT;
    static const QString URL;
    static const QString WIDTH;

    EmbedVideo() {}
    EmbedVideo(const QByteArray &json) : JsonSerializable(json) {}
    EmbedVideo(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedVideo(const QString &json) : JsonSerializable(json) {}

    void setHeight(const QJsonValue &height);
    void setUrl(const QJsonValue &url);
    void setWidth(const QJsonValue &width);
    QJsonValue getHeight() const;
    QJsonValue getUrl() const;
    QJsonValue getWidth() const;

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue height READ getHeight WRITE setHeight)
    Q_PROPERTY(QJsonValue width READ getWidth WRITE setWidth)
};

Q_DECLARE_METATYPE(EmbedVideo)

#endif // EMBEDVIDEO_H
