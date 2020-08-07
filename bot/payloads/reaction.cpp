#include "reaction.h"

const QString Reaction::COUNT = "count";
const QString Reaction::EMOJI = "emoji";
const QString Reaction::ME = "me";

QJsonValue
Reaction::getCount() const {
    return _jsonObject[COUNT];
}

void
Reaction::setCount(const QJsonValue &count) {
    _jsonObject[COUNT] = count;
}

QJsonValue
Reaction::getMe() const {
    return _jsonObject[ME];
}

void
Reaction::setMe(const QJsonValue &me) {
    _jsonObject[ME] = me;
}

QJsonObject
Reaction::getEmoji() const {
    return _jsonObject[EMOJI].toObject();
}

void
Reaction::setEmoji(const QJsonObject &emoji) {
    _jsonObject[EMOJI] = emoji;
}
