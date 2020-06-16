#include "updatestatus.h"

void
UpdateStatus::read(const QJsonObject &jsonObject) {
    if (!jsonObject[SINCE].isNull()) {
        since = QSharedPointer<int>(new int(jsonObject[SINCE].toInt()));
    }

    if (!jsonObject[GAME].isNull()) {
        game = QSharedPointer<Activity>(new Activity);
        game->read(jsonObject[GAME].toObject());
    }

    status = jsonObject[STATUS].toString();
    afk = jsonObject[AFK].toBool();
}

void
UpdateStatus::write(QJsonObject &jsonObject) const {
    if (since != nullptr) {
        jsonObject[SINCE] = *since.get();
    } else {
        jsonObject[SINCE] = QJsonValue::Null;
    }

    if (game != nullptr) {
        jsonObject[GAME] = game->toQJsonObject();
    } else {
        jsonObject[GAME] = QJsonValue::Null;
    }

    jsonObject[STATUS] = status;
    jsonObject[AFK] = afk;
}
