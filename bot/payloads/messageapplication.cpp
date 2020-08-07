#include "messageapplication.h"


const QString MessageApplication::TYPE = "type";
const QString MessageApplication::COVER_IMAGE = "cover_image";
const QString MessageApplication::DESCRIPTION = "description";
const QString MessageApplication::NAME = "name";
const QString MessageApplication::ICON = "icon";

QJsonValue
MessageApplication::getType() const {
    return _jsonObject[TYPE];
}

void
MessageApplication::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
MessageApplication::getCoverImage() const {
    return _jsonObject[COVER_IMAGE];
}

void
MessageApplication::setCoverImage(const QJsonValue &coverImage) {
    _jsonObject[COVER_IMAGE] = coverImage;
}

QJsonValue
MessageApplication::getDescription() const {
    return _jsonObject[DESCRIPTION];
}

void
MessageApplication::setDescription(const QJsonValue &description) {
    _jsonObject[DESCRIPTION] = description;
}

QJsonValue
MessageApplication::getIcon() const {
    return _jsonObject[ICON];
}

void
MessageApplication::setIcon(const QJsonValue &icon) {
    _jsonObject[ICON] = icon;
}

QJsonValue
MessageApplication::getName() const {
    return _jsonObject[NAME];
}

void
MessageApplication::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}
