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

#ifndef EMBED_H
#define EMBED_H

#include "jsonserializable.h"


class Embed : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString TITLE;
    static const QString TYPE;
    static const QString DESCRIPTION;
    static const QString URL;
    static const QString TIMESTAMP;
    static const QString COLOR;
    static const QString FOOTER;
    static const QString IMAGE;
    static const QString THUMBNAIL;
    static const QString VIDEO;
    static const QString PROVIDER;
    static const QString AUTHOR;
    static const QString FIELDS;

    Embed() {}
    Embed(const QByteArray &json) : JsonSerializable(json) {}
    Embed(const QJsonObject &json) : JsonSerializable(json) {}
    Embed(const QString &json) : JsonSerializable(json) {}

    QJsonArray getFields() const;
    QJsonObject getAuthor() const;
    QJsonObject getFooter() const;
    QJsonObject getImage() const;
    QJsonObject getProvider() const;
    QJsonObject getThumbnail() const;
    QJsonObject getVideo() const;
    QJsonValue getColor() const;
    QJsonValue getDescription() const;
    QJsonValue getTimestamp() const;
    QJsonValue getTitle() const;
    QJsonValue getType() const;
    QJsonValue getUrl() const;
    void setAuthor(const QJsonObject &author);
    void setColor(const QJsonValue &color);
    void setDescription(const QJsonValue &description);
    void setFields(const QJsonArray &fields);
    void setFooter(const QJsonObject &footer);
    void setImage(const QJsonObject &image);
    void setProvider(const QJsonObject &provider);
    void setThumbnail(const QJsonObject &thumbnail);
    void setTimestamp(const QJsonValue &timestamp);
    void setTitle(const QJsonValue &title);
    void setType(const QJsonValue &type);
    void setUrl(const QJsonValue &url);
    void setVideo(const QJsonObject &video);

    Q_PROPERTY(QJsonValue title READ getTitle WRITE setTitle)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue description READ getDescription WRITE setDescription)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue timestamp READ getTimestamp WRITE setTimestamp)
    Q_PROPERTY(QJsonValue color READ getColor WRITE setColor)
    Q_PROPERTY(QJsonObject footer READ getFooter WRITE setFooter)
    Q_PROPERTY(QJsonObject image READ getImage WRITE setImage)
    Q_PROPERTY(QJsonObject thumbnail READ getThumbnail WRITE setThumbnail)
    Q_PROPERTY(QJsonObject video READ getVideo WRITE setVideo)
    Q_PROPERTY(QJsonObject provider READ getProvider WRITE setProvider)
    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QJsonArray fields READ getFields WRITE setFields)
};

Q_DECLARE_METATYPE(Embed)

#endif // EMBED_H
