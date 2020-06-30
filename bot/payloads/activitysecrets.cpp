#include "activitysecrets.h"

#include <util/jsonutils.h>

QString
ActivitySecrets::getJoin() {
    return join;
}

void
ActivitySecrets::setJoin(QString join) {
    this->join = join;
}

QString
ActivitySecrets::getSpectate() {
    return spectate;
}

void
ActivitySecrets::setSpectate(QString spectate) {
    this->spectate = spectate;
}

QString
ActivitySecrets::getMatch() {
    return match;
}

void
ActivitySecrets::setMatch(QString match) {
    this->match = match;
}

void
ActivitySecrets::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
ActivitySecrets::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
