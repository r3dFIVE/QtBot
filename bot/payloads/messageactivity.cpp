#include "messageactivity.h"


const QString MessageActivity::PARTY_ID = "party_id";
const QString MessageActivity::TYPE = "type";

QJsonValue
MessageActivity::getPartyId() const {
    return _jsonObject[PARTY_ID];
}

void
MessageActivity::setPartyId(const QJsonValue &partyId) {
    _jsonObject[PARTY_ID] = partyId;
}

QJsonValue
MessageActivity::getType() const {
    return _jsonObject[TYPE];
}

void
MessageActivity::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}
