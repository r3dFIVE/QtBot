#ifndef PRESENCE_H
#define PRESENCE_H

#include "activity.h"
#include "jsonserializeable.h"

#include <QSharedPointer>


class UpdateStatus : public JsonSerializeable
{
    const QString SINCE = "since";
    const QString GAME = "game";
    const QString STATUS = "status";
    const QString AFK = "afk";

public:
    QSharedPointer<int> since;
    QSharedPointer<Activity> game;
    QString status;
    bool afk;

    void read(const QJsonObject &jsonObject) override {
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

    void write(QJsonObject &jsonObject) const override {
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
};


#endif // PRESENCE_H
