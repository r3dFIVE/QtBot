#include "updatestatus.h"


const QString UpdateStatus::SINCE = "since";
const QString UpdateStatus::GAME = "game";
const QString UpdateStatus::STATUS = "status";
const QString UpdateStatus::AFK = "afk";

QJsonValue
UpdateStatus::getSince() const {
    return _jsonObject[SINCE];
}

void
UpdateStatus::setSince(const QJsonValue &since) {
    _jsonObject[SINCE] = since;
}

QJsonObject
UpdateStatus::getGame() const {
    return _jsonObject[GAME].toObject();
}

void
UpdateStatus::setGame(const QJsonObject &game) {
    _jsonObject[GAME] = game;
}

QJsonValue
UpdateStatus::getStatus() const {
    return _jsonObject[STATUS];
}

void
UpdateStatus::setStatus(const QJsonValue &status) {
    _jsonObject[STATUS] = status;
}

QJsonValue
UpdateStatus::getAfk() const {
    return _jsonObject[AFK];
}

void
UpdateStatus::setAfk(const QJsonValue &afk) {
    _jsonObject[AFK] = afk;
}
