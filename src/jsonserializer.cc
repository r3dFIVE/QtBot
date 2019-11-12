#include "jsonserializer.h"

#include <QJsonObject>
#include <QJsonDocument>

QString
JsonSerializer::toQString(JsonSerializeable &serializeable) {
    return QString(JsonSerializer::toByteArray(serializeable));
}

QByteArray
JsonSerializer::toByteArray(JsonSerializeable &serializeable) {
    QJsonObject jsonObject;
    serializeable.write(jsonObject);
    QJsonDocument document(jsonObject);
    return document.toJson(QJsonDocument::Compact);
}

void
JsonSerializer::fromByteArray(const QByteArray &json, JsonSerializeable &serializeable) {
    QJsonDocument document = QJsonDocument::fromJson(json);
    QJsonObject object = document.object();
    serializeable.read(object);
}

void
JsonSerializer::fromQString(const QString &json, JsonSerializeable &serializeable) {
    JsonSerializer::fromByteArray(json.toUtf8(), serializeable);
}
