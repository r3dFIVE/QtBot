#include "reaction.h"

#include "util/serializationutils.h"


QJsonValue
Reaction::getCount() const {
    return count;
}

void
Reaction::setCount(const QJsonValue &value) {
    count = value;
}

QJsonValue
Reaction::getMe() const {
    return me;
}

void
Reaction::setMe(const QJsonValue &value) {
    me = value;
}

QJsonObject
Reaction::getEmoji() const {
    if (emoji) {
        return emoji->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Reaction::setEmoji(const QJsonObject &value) {
    if (!value.isEmpty()) {
        emoji = QSharedPointer<Emoji>(new Emoji);
        SerializationUtils::readFromJson(*emoji, value);
    }
}

void
Reaction::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Reaction::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}

