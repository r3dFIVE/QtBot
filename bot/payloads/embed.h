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

#ifndef EMBED_H
#define EMBED_H

#include "embedauthor.h"
#include "embedfield.h"
#include "embedfooter.h"
#include "embedmedia.h"
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

    Embed(QObject *parent = nullptr) : JsonSerializable(parent) {}
    Embed(const Embed &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    Embed(const QString &title,
          const QString &description,
          const QString &url,
          const int color,
          QObject *parent = nullptr);
    Embed(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Embed(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    Embed(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    Q_INVOKABLE QJsonArray getFields() const;
    Q_INVOKABLE QJsonObject getAuthor() const;
    Q_INVOKABLE QJsonObject getFooter() const;
    Q_INVOKABLE QJsonObject getImage() const;
    Q_INVOKABLE QJsonObject getThumbnail() const;
    Q_INVOKABLE QJsonObject getVideo() const;
    Q_INVOKABLE QJsonValue getColor() const;
    Q_INVOKABLE QJsonValue getDescription() const;
    Q_INVOKABLE QJsonValue getTimestamp() const;
    Q_INVOKABLE QJsonValue getTitle() const;
    Q_INVOKABLE QJsonValue getType() const;
    Q_INVOKABLE QJsonValue getUrl() const;
    Q_INVOKABLE void setAuthor(EmbedAuthor *author);
    Q_INVOKABLE void setAuthor(const QJsonObject &author);
    Q_INVOKABLE void setColor(const QJsonValue &color);
    Q_INVOKABLE void setDescription(const QJsonValue &description);
    Q_INVOKABLE void addField(EmbedField *field);
    Q_INVOKABLE void addField(const QJsonObject &field);
    Q_INVOKABLE void setFields(const QJsonArray &fields);
    Q_INVOKABLE void setFooter(EmbedFooter *footer);
    Q_INVOKABLE void setFooter(const QJsonObject &footer);
    Q_INVOKABLE void setImage(EmbedMedia *image);
    Q_INVOKABLE void setImage(const QJsonObject &image);
    Q_INVOKABLE void setThumbnail(EmbedMedia *thumbnail);
    Q_INVOKABLE void setThumbnail(const QJsonObject &thumbnail);
    Q_INVOKABLE void setTimestamp(const QJsonValue &timestamp);
    Q_INVOKABLE void setTitle(const QJsonValue &title);
    Q_INVOKABLE void setType(const QJsonValue &type);
    Q_INVOKABLE void setUrl(const QJsonValue &url);
    Q_INVOKABLE void setVideo(EmbedMedia *video);
    Q_INVOKABLE void setVideo(const QJsonObject &video);

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
    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QJsonArray fields READ getFields WRITE setFields)
};

Q_DECLARE_METATYPE(Embed)

#endif // EMBED_H
