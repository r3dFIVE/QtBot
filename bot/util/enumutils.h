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

#ifndef ENUMUTILS_H
#define ENUMUTILS_H

#include <QObject>
#include <QMetaEnum>
#include <QJsonValue>


class EnumUtils : public QObject
{
    Q_OBJECT

public:
    template <class T>
    static QString valueToKey(const T &t) {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return metaEnum.valueToKey(t);
    };

    template <class T>
    static int keyToValue(const int &key) {
        QByteArray byteArray;

        byteArray.setNum(key);

        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return metaEnum.keyToValue(byteArray);
    }

    template <class T>
    static T keyToValue(const QByteArray &key) {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return (T) metaEnum.keyToValue(key);
    }

    template <class T>
    static T keyToValue(const QJsonValue &json) {
        QByteArray key = json.toString().toUtf8();

        QMetaEnum metaEnum = QMetaEnum::fromType<T>();

        return (T) metaEnum.keyToValue(key);
    }
};

#endif // ENUMUTILS_H
