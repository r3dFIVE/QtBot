#ifndef PRESENCE_H
#define PRESENCE_H

#include "activity.h"
#include "jsonserializeable.h"

#include <QSharedPointer>


class UpdateStatus : public JsonSerializeable
{
    Q_OBJECT

public:
    const QString SINCE = "since";
    const QString GAME = "game";
    const QString STATUS = "status";
    const QString AFK = "afk";

    Q_PROPERTY(QJsonValue since READ getSince WRITE setSince)
    QSharedPointer<int> since;

    Q_PROPERTY(QJsonObject game READ getGame WRITE setGame)
    QSharedPointer<Activity> game;

    Q_PROPERTY(QString status READ getStatus WRITE setStatus)
    QString status;

    Q_PROPERTY(bool afk READ getAfk WRITE setAfk)
    bool afk;

    QJsonValue
    getSince() {
        if (since) {
            return QJsonValue(*since);
        } else {
            return QJsonValue();
        }
    }

    void
    setSince(QJsonValue since) {
        if (!since.isNull()) {
            this->since = QSharedPointer<int>(new int(since.toInt()));
        }
    }

    QJsonObject
    getGame() {
        if (game) {
            return game->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setGame(QJsonObject game) {
        if (!this->game) {
            this->game = QSharedPointer<Activity>(new Activity);
        }
        JsonUtils::readFromJson(*this->game, game);
    }

    QString
    getStatus() {
        return status;
    }

    void
    setStatus(QString status) {
        this->status = status;
    }

    bool
    getAfk() {
        return afk;
    }

    void
    setAfk(bool afk) {
        this->afk = afk;
    }

    void
    read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void
    write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(UpdateStatus)

#endif // PRESENCE_H
