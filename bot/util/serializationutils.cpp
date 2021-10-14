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

#include "serializationutils.h"

#include <QMetaProperty>

void
SerializationUtils::readFromJson(JsonSerializable &target, const QJsonObject &source) {
    QMetaObject metaObject = *target.metaObject();
    for (int i = metaObject.propertyOffset(); i < metaObject.propertyCount(); ++i) {
        QMetaProperty metaProperty = metaObject.property(i);
        if (source.contains(metaProperty.name())) {
            int type = source[metaProperty.name()].type();
            switch (type) {
                case QJsonValue::Bool:
                case QJsonValue::Double:
                case QJsonValue::String:
                    metaProperty.write(&target, source[metaProperty.name()]);
                    break;
                case QJsonValue::Array:
                    metaProperty.write(&target, source[metaProperty.name()].toArray());
                    break;
                case QJsonValue::Object:
                    metaProperty.write(&target, source[metaProperty.name()].toObject());
                    break;
            }
        }
    }
}

void
SerializationUtils::writeToJson(const JsonSerializable &source, QJsonObject &target) {
    QMetaObject metaObject = *source.metaObject();
    for (int i = metaObject.propertyOffset(); i < metaObject.propertyCount(); ++i) {
        QMetaProperty property = metaObject.property(i);
        QVariant variant = property.read(&source);

        if (variant.isNull()) {
            continue;
        }

        switch(QMetaType::Type(variant.type())) {
            case QMetaType::Int:
                target[property.name()] = variant.toInt();
                break;

            case QMetaType::Bool:
                target[property.name()] = variant.toBool();
                break;

            case QMetaType::QString:
                target[property.name()] = variant.toString();
                break;

            case QMetaType::QJsonValue:
                target[property.name()] = variant.toJsonValue();
                break;

            case QMetaType::QJsonObject: {
                target[property.name()] = variant.toJsonObject();
                break;
            }
            case QMetaType::QJsonArray: {
                target[property.name()] = variant.toJsonArray();
                break;
            default:
                break;
            }
        }
    }
}

QJsonObject
SerializationUtils::toQJsonObject(const JsonSerializable &source) {
    QJsonObject jsonObject;
    writeToJson(source, jsonObject);
    return jsonObject;
}

QByteArray
SerializationUtils::toQByteArray(const JsonSerializable &source) {
    QJsonDocument document(toQJsonObject(source));
    return document.toJson(QJsonDocument::Compact);
}

QByteArray SerializationUtils::toQByteArray(const QJsonObject &source) {
    return QJsonDocument(source).toJson();
}

QJsonDocument
SerializationUtils::toJsonDocument(const JsonSerializable &source) {
    return QJsonDocument(toQJsonObject(source));
}

QVariant
SerializationUtils::toVariant(const JsonSerializable &source) {
    return toJsonDocument(source).toVariant();
}

QString
SerializationUtils::toQString(const JsonSerializable &source) {
    return QString(toQByteArray(source));
}

void
SerializationUtils::fromQJsonObject(JsonSerializable &target, const QJsonObject &source) {
    readFromJson(target, source);
}

void
SerializationUtils::fromQString(JsonSerializable &target, const QString &source) {
    fromQByteArray(target, source.toUtf8());
}

void
SerializationUtils::fromQByteArray(JsonSerializable &target, const QByteArray &source) {
    QJsonDocument document = QJsonDocument::fromJson(source);
    QJsonObject object = document.object();
    readFromJson(target, object);
}

void
SerializationUtils::fromJsonDocument(JsonSerializable &target, const QJsonDocument &source) {
    readFromJson(target, source.object());
}

void
SerializationUtils::fromVariant(JsonSerializable &target, const QVariant &source) {
    QJsonObject object = QJsonObject::fromVariantMap(source.toMap());
    readFromJson(target, object);
}
