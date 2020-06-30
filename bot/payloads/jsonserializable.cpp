#include "jsonserializable.h"

#include "util/jsonutils.h"


QJsonObject
JsonSerializable::toQJsonObject() {
    QJsonObject jsonObject;
    this->write(jsonObject);
    return jsonObject;
}

QByteArray
JsonSerializable::toByteArray() {
    QJsonDocument document(this->toQJsonObject());
    return document.toJson(QJsonDocument::Compact);
}

QString
JsonSerializable::toQString() {
    return QString(this->toByteArray());
}

void
JsonSerializable::fromQJsonObject(const QJsonObject &json) {
    this->read(json);
}

void
JsonSerializable::fromQString(const QString &json) {
    this->fromByteArray(json.toUtf8());
}

void
JsonSerializable::fromByteArray(const QByteArray &json) {
    QJsonDocument document = QJsonDocument::fromJson(json);
    QJsonObject object = document.object();
    this->read(object);
}
