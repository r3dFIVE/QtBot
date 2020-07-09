#include "messageapplication.h"

#include "util/serializationutils.h"


QJsonValue
MessageApplication::getType() const {
    return type;
}

void
MessageApplication::setType(const QJsonValue &value) {
    type = value;
}

QJsonValue
MessageApplication::getCoverImage() const {
    return cover_image;
}

void
MessageApplication::setCoverImage(const QJsonValue &value) {
    cover_image = value;
}

QJsonValue
MessageApplication::getDescription() const {
    return description;
}

void
MessageApplication::setDescription(const QJsonValue &value) {
    description = value;
}

QJsonValue
MessageApplication::getIcon() const {
    return icon;
}

void
MessageApplication::setIcon(const QJsonValue &value) {
    icon = value;
}

QJsonValue
MessageApplication::getName() const {
    return name;
}

void
MessageApplication::setName(const QJsonValue &value) {
    name = value;
}

void
MessageApplication::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
MessageApplication::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
