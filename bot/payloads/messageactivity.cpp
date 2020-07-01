#include "messageactivity.h"

#include "util/jsonutils.h"


QJsonValue
MessageActivity::getPartyId() const {
    return party_id;
}

void
MessageActivity::setPartyId(const QJsonValue &value) {
    party_id = value;
}

QJsonValue
MessageActivity::getType() const {
    return type;
}

void
MessageActivity::setType(const QJsonValue &value) {
    type = value;
}

void
MessageActivity::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
MessageActivity::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
