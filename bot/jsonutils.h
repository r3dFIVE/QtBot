#ifndef JSONUTILS_H
#define JSONUTILS_H

#include "typefactory.h"
#include "logging/logfactory.h"
#include "payloads/jsonserializable.h"

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMetaProperty>
#include <QSharedPointer>
#include <QTypeInfo>


struct JsonUtils
{
    static void
    readFromJson(QObject &target, const QJsonObject &source) {
        QMetaObject metaObject = *target.metaObject();
        for (int i = metaObject.propertyOffset(); i < metaObject.propertyCount(); ++i) {
            QMetaProperty metaProperty = metaObject.property(i);
            if (source.contains(metaProperty.name())) {
                int type = source[metaProperty.name()].type();
                switch (type) {
                    case QJsonValue::Bool: {
                        metaProperty.write(&target, source[metaProperty.name()].toBool());
                        break;
                    }
                    case QJsonValue::Double: {
                        // Discord only sends ints, all numerical Json values are considered double.
                        // Doubles are serialized as strings in discord API.
                        // Keeping as ints because some are used for bitmastking;
                        metaProperty.write(&target, source[metaProperty.name()].toInt());
                        break;
                    }
                    case QJsonValue::String: {
                        metaProperty.write(&target, source[metaProperty.name()].toString());
                        break;
                    }
                    case QJsonValue::Array: {
                        metaProperty.write(&target, source[metaProperty.name()].toArray());
                        break;
                    }
                    case QJsonValue::Object: {
                        metaProperty.write(&target, source[metaProperty.name()].toObject());
                        break;
                    }
                }
            }
        }
    }

    static void
    writeToJson(QObject &source, QJsonObject &target) {
        QMetaObject metaObject = *source.metaObject();
        for (int i = metaObject.propertyOffset(); i < metaObject.propertyCount(); ++i) {
            QMetaProperty property = metaObject.property(i);
            QVariant variant = property.read(&source);

            if (variant.isNull()) {
                continue;
            }

            switch(QMetaType::Type(variant.type())) {
                case QMetaType::Int: {
                    target[property.name()] = variant.toInt();
                    break;
                }
                case QMetaType::Bool: {
                    target[property.name()] = variant.toBool();
                    break;
                }
                case QMetaType::QString: {
                    target[property.name()] = variant.toString();
                    break;
                }
                case QMetaType::QJsonValue: {
                    target[property.name()] = variant.toJsonValue();
                    break;
                }
                case QMetaType::QJsonObject: {
                    QJsonObject jsonObject = variant.toJsonObject();
                    if (!jsonObject.isEmpty()) {
                        target[property.name()] = jsonObject;
                    }
                    break;
                }
                case QMetaType::QJsonArray: {
                    QJsonArray jsonArray = variant.toJsonArray();
                    if (!jsonArray.isEmpty()) {
                        target[property.name()] = jsonArray;
                    }
                    break;
                }
            }
        }
    }

    static QJsonObject
    toQJsonObject(QObject &source) {
        QJsonObject jsonObject;
        writeToJson(source, jsonObject);
        return jsonObject;
    }

    static QByteArray
    toQByteArray(QObject &source) {
        QJsonDocument document(toQJsonObject(source));
        return document.toJson(QJsonDocument::Compact);
    }

    static QString
    toQString(QObject &source) {
        return QString(toQByteArray(source));
    }

    static void
    fromQJsonObject(QObject &target, const QJsonObject &source) {
        readFromJson(target, source);
    }

    static void
    fromQString(QObject &target, const QString &source) {
        fromQByteArray(target, source.toUtf8());
    }

    static void
    fromQByteArray(QObject &target, const QByteArray &source) {
        QJsonDocument document = QJsonDocument::fromJson(source);
        QJsonObject object = document.object();
        readFromJson(target, object);
    }
};

#endif // JSONUTILS_H
