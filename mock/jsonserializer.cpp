#include "jsonserializer.h"

#include <QJsonObject>
#include <QJsonDocument>

QString
JsonSerializer::toQString(const JsonSerializeable &serializeable) {
    return QString(JsonSerializer::toByteArray(serializeable));
}

QByteArray
JsonSerializer::toByteArray(const JsonSerializeable &serializeable) {
    QJsonObject jsonObject;
    serializeable.write(jsonObject);
    QJsonDocument document(jsonObject);
    return document.toJson(QJsonDocument::Compact);
}

QJsonObject
JsonSerializer::toQJsonObject(const JsonSerializeable &serializeable) {
    QJsonObject jsonObject;
    serializeable.write(jsonObject);
    return jsonObject;
}

void
JsonSerializer::fromByteArray(JsonSerializeable &serializeable, const QByteArray &json) {
    QJsonDocument document = QJsonDocument::fromJson(json);
    QJsonObject object = document.object();
    JsonSerializer::fromQJsonObject(serializeable, object);
}

void
JsonSerializer::fromQString(JsonSerializeable &serializeable, const QString &json) {
    JsonSerializer::fromByteArray(serializeable, json.toUtf8());
}

void
JsonSerializer::fromQJsonObject(JsonSerializeable &serializeable, const QJsonObject &json) {
    serializeable.read(json);
}
