#include "activityemoji.h"

const QString ActivityEmoji::NAME = "name";
const QString ActivityEmoji::ID = "id";
const QString ActivityEmoji::ANIMATED = "animated";

QJsonValue
ActivityEmoji::getName() const {
    return _jsonObject[NAME];
}

void
ActivityEmoji::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
ActivityEmoji::getId() const {
    return _jsonObject[ID];
}

void
ActivityEmoji::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
ActivityEmoji::getAnimated() const {
    return _jsonObject[ANIMATED];
}

void
ActivityEmoji::setAnimated(const QJsonValue &animated) {
    _jsonObject[ANIMATED] = animated;
}
