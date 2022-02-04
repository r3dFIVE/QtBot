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

    EmbedAuthor(QObject *parent = nullptr) : JsonSerializable(parent) {}
    EmbedAuthor(const EmbedAuthor &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    EmbedAuthor(const QString &name,
                const QString &url,
                const QString &iconUrl,
                QObject *parent = nullptr);
    EmbedAuthor(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    EmbedAuthor(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    EmbedAuthor(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

    Q_INVOKABLE QJsonValue getIconUrl() const;
    Q_INVOKABLE QJsonValue getName() const;
    Q_INVOKABLE QJsonValue getProxyIconUrl() const;
    Q_INVOKABLE QJsonValue getUrl() const;
    Q_INVOKABLE void setIconUrl(const QJsonValue &iconUrl);
    Q_INVOKABLE void setName(const QJsonValue &name);
    Q_INVOKABLE void setProxyIconUrl(const QJsonValue &proxyIconUrl);
    Q_INVOKABLE void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
};

Q_DECLARE_METATYPE(EmbedAuthor)

#endif // EMBEDAUTHOR_H
