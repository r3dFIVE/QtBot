#include "activityparty.h"

const QString ActivityParty::ID = "id";
const QString ActivityParty::SIZE = "size";

QJsonValue
ActivityParty::getId() const {
    return _jsonObject[ID].toString();
}

void
ActivityParty::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonArray
ActivityParty::getSize() const {
    return _jsonObject[SIZE].toArray();
}

void
ActivityParty::setSize(const QJsonArray &size) {
    _jsonObject[SIZE] = size;
}

