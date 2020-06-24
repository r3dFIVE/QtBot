#include "updatestatus.h"

#include <jsonutils.h>

QJsonValue
UpdateStatus::getSince() {
    if (since) {
        return QJsonValue(*since);
    } else {
        return QJsonValue();
    }
}

void
UpdateStatus::setSince(QJsonValue since) {
    if (!since.isNull()) {
        this->since = QSharedPointer<int>(new int(since.toInt()));
    }
}

QJsonObject
UpdateStatus::getGame() {
    if (game) {
        return game->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
UpdateStatus::setGame(QJsonObject game) {
    this->game = QSharedPointer<Activity>(new Activity);
    JsonUtils::readFromJson(*this->game, game);
}

QString
UpdateStatus::getStatus() {
    return status;
}

void
UpdateStatus::setStatus(QString status) {
    this->status = status;
}

bool
UpdateStatus::getAfk() {
    return afk;
}

void
UpdateStatus::setAfk(bool afk) {
    this->afk = afk;
}

void
UpdateStatus::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
UpdateStatus::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);

    if (!jsonObject.contains(SINCE)) {
        jsonObject[SINCE] = QJsonValue::Null;
    }

    if (!jsonObject.contains(GAME)) {
        jsonObject[GAME] = QJsonValue::Null;
    }
}
