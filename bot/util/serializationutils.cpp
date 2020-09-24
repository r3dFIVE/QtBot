#include "serializationutils.h"

void
SerializationUtils::readFromJson(QObject &target, const QJsonObject &source) {
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
SerializationUtils::writeToJson(const QObject &source, QJsonObject &target) {
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
            }
        }
    }
}

QJsonObject
SerializationUtils::toQJsonObject(const QObject &source) {
    QJsonObject jsonObject;
    writeToJson(source, jsonObject);
    return jsonObject;
}

QByteArray
SerializationUtils::toQByteArray(const QObject &source) {
    QJsonDocument document(toQJsonObject(source));
    return document.toJson(QJsonDocument::Compact);
}

QByteArray SerializationUtils::toQByteArray(const QJsonObject &source) {
    return QJsonDocument(source).toJson();
}

QJsonDocument
SerializationUtils::toJsonDocument(const QObject &source) {
    return QJsonDocument(toQJsonObject(source));
}

QVariant
SerializationUtils::toVariant(const QObject &source) {
    return toJsonDocument(source).toVariant();
}

QString
SerializationUtils::toQString(const QObject &source) {
    return QString(toQByteArray(source));
}

void
SerializationUtils::fromQJsonObject(QObject &target, const QJsonObject &source) {
    readFromJson(target, source);
}

void
SerializationUtils::fromQString(QObject &target, const QString &source) {
    fromQByteArray(target, source.toUtf8());
}

void
SerializationUtils::fromQByteArray(QObject &target, const QByteArray &source) {
    QJsonDocument document = QJsonDocument::fromJson(source);
    QJsonObject object = document.object();
    readFromJson(target, object);
}

void
SerializationUtils::fromJsonDocument(QObject &target, const QJsonDocument &source) {
    readFromJson(target, source.object());
}

void
SerializationUtils::fromVariant(QObject &target, const QVariant &source) {
    QJsonObject object = QJsonObject::fromVariantMap(source.toMap());
    readFromJson(target, object);
}
