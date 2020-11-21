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

#ifndef JSONSERIALIZEABLE_H
#define JSONSERIALIZEABLE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class JsonSerializable : public QObject
{
    Q_OBJECT

protected:
    QJsonObject _jsonObject;

public:
    JsonSerializable() {}
    JsonSerializable(const JsonSerializable &other) {
        _jsonObject = other._jsonObject;
    }
    JsonSerializable(const QByteArray &json);
    JsonSerializable(const QJsonObject &json);
    JsonSerializable(const QString &json);
    ~JsonSerializable() {}

    QByteArray toByteArray();
    QJsonObject fromQString(const QString &json);
    QJsonObject fromByteArray(const QByteArray &json);
    QJsonObject toQJsonObject();
    QString toQString();    
    void setQJsonObject(const QJsonObject &jsonObject);
};

Q_DECLARE_METATYPE(JsonSerializable*)

#endif // JSONSERIALIZEABLE_H
