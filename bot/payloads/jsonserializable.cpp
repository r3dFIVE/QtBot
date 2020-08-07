#include "jsonserializable.h"


JsonSerializable::JsonSerializable(const QJsonObject &json) {
    _jsonObject = json;
}

JsonSerializable::JsonSerializable(const QString &json) {
    _jsonObject = fromQString(json);
}

JsonSerializable::JsonSerializable(const QByteArray &json) {
    _jsonObject = fromByteArray(json);
}

void
JsonSerializable::setQJsonObject(const QJsonObject &jsonObject) {
    _jsonObject = jsonObject;
}

QJsonObject
JsonSerializable::toQJsonObject() {
    return _jsonObject;
}

QByteArray
JsonSerializable::toByteArray() {
    QJsonDocument document(_jsonObject);

    return document.toJson(QJsonDocument::Compact);
}

QString
JsonSerializable::toQString() {
    return QString(toByteArray());
}

QJsonObject
JsonSerializable::fromQString(const QString &json) {
    return fromByteArray(json.toUtf8());
}

QJsonObject
JsonSerializable::fromByteArray(const QByteArray &json) {
    QJsonDocument document = QJsonDocument::fromJson(json);

    QJsonObject jsonObject = document.object();

    _jsonObject = jsonObject;

    return _jsonObject;
}
