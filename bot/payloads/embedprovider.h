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

#ifndef EMBEDPROVIDER_H
#define EMBEDPROVIDER_H

#include "jsonserializable.h"


class EmbedProvider : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString NAME;
    static const QString URL;

    EmbedProvider() {}
    EmbedProvider(const QByteArray &json) : JsonSerializable(json) {}
    EmbedProvider(const QJsonObject &json) : JsonSerializable(json) {}
    EmbedProvider(const QString &json) : JsonSerializable(json) {}

    QJsonValue getName() const;
    QJsonValue getUrl() const;
    void setName(const QJsonValue &name);
    void setUrl(const QJsonValue &url);

    Q_PROPERTY(QJsonValue url READ getUrl WRITE setUrl)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
};

Q_DECLARE_METATYPE(EmbedProvider)

#endif // EMBEDPROVIDER_H
