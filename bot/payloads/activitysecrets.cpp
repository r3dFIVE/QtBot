#include "activitysecrets.h"

const QString ActivitySecrets::JOIN = "join";
const QString ActivitySecrets::MATCH = "match";
const QString ActivitySecrets::SPECTATE = "spectate";

QJsonValue
ActivitySecrets::getJoin() {
    return _jsonObject[JOIN].toString();
}

void
ActivitySecrets::setJoin(const QJsonValue &join) {
   _jsonObject[JOIN] = join;
}

QJsonValue
ActivitySecrets::getSpectate() {
    return _jsonObject[SPECTATE].toString();
}

void
ActivitySecrets::setSpectate(const QJsonValue &spectate) {
   _jsonObject[SPECTATE] = spectate;
}

QJsonValue
ActivitySecrets::getMatch() {
    return _jsonObject[MATCH].toString();
}

void
ActivitySecrets::setMatch(const QJsonValue &match) {
    _jsonObject[MATCH] = match;
}


