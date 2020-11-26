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

#ifndef ASSETS_H
#define ASSETS_H

#include "jsonserializable.h"


class ActivityAssets : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString LARGE_IMAGE;
    static const QString LARGE_TEXT;
    static const QString SMALL_IMAGE;
    static const QString SMALL_TEXT;

    ActivityAssets() {}
    ActivityAssets(const QByteArray &json) : JsonSerializable(json) {}
    ActivityAssets(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityAssets(const QString &json) : JsonSerializable(json) {}

    QJsonValue getLargeText();
    QJsonValue getSmallImage();
    QJsonValue getSmallText();
    QJsonValue getLargeImage();
    void setLargeImage(const QJsonValue &largeImage);
    void setLargeText(const QJsonValue &largeText);
    void setSmallImage(const QJsonValue &smallImage);
    void setSmallText(const QJsonValue &smallText);

    Q_PROPERTY(QJsonValue large_image READ getLargeImage WRITE setLargeImage)
    Q_PROPERTY(QJsonValue large_text READ getLargeText WRITE setLargeText)
    Q_PROPERTY(QJsonValue small_image READ getSmallImage WRITE setSmallImage)
    Q_PROPERTY(QJsonValue small_text READ getSmallText WRITE setSmallText)
};

Q_DECLARE_METATYPE(ActivityAssets)

#endif // ASSETS_H


