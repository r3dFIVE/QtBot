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

#ifndef MESSAGEAPPLICATION_H
#define MESSAGEAPPLICATION_H

#include "jsonserializable.h"


class MessageApplication : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString TYPE;
    static const QString COVER_IMAGE;
    static const QString DESCRIPTION;
    static const QString NAME;
    static const QString ICON;

    MessageApplication() {}
    MessageApplication(const QByteArray &json) : JsonSerializable(json) {}
    MessageApplication(const QJsonObject &json) : JsonSerializable(json) {}
    MessageApplication(const QString &json) : JsonSerializable(json) {}

    QJsonValue getCoverImage() const;
    QJsonValue getDescription() const;
    QJsonValue getIcon() const;
    QJsonValue getName() const;
    QJsonValue getType() const;
    void setCoverImage(const QJsonValue &coverImage);
    void setDescription(const QJsonValue &description);
    void setIcon(const QJsonValue &icon);
    void setName(const QJsonValue &name);
    void setType(const QJsonValue &type);

    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue cover_image READ getCoverImage WRITE setCoverImage)
    Q_PROPERTY(QJsonValue description READ getDescription WRITE setDescription)
    Q_PROPERTY(QJsonValue icon READ getIcon WRITE setIcon)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
};

Q_DECLARE_METATYPE(MessageApplication)
#endif // MESSAGEAPPLICATION_H
