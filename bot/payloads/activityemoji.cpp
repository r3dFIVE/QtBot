#include "activityemoji.h"

#include <util/serializationutils.h>

QString
ActivityEmoji::getName() {
    return name;
}

void
ActivityEmoji::setName(QString name) {
    this->name = name;
}

QString
ActivityEmoji::getId() {
    return id;
}

void
ActivityEmoji::setId(QString id) {
    this->id = id;
}

QJsonValue
ActivityEmoji::getAnimated() {
    if (animated) {
        return QJsonValue(*animated);
    }
    return QJsonValue();
}

void
ActivityEmoji::setAnimated(QJsonValue animated) {
    if (!animated.isNull()) {
        this->animated = QSharedPointer<bool>(new bool(animated.toBool()));
    }
}

void
ActivityEmoji::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
ActivityEmoji::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
