#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "jsonserializeable.h"
#include "timestamps.h"
#include "emoji.h"
#include "party.h"
#include "assets.h"
#include "secrets.h"

#include <QSharedPointer>

class Activity : public JsonSerializeable
{
    Q_OBJECT

    const QString NAME = "name";
    const QString TYPE = "type";
    const QString URL = "url";
    const QString CREATED_AT = "created_at";
    const QString TIMESTAMPS = "timestamps";
    const QString APPLICATION_ID = "application_id";
    const QString DETAILS = "details";
    const QString STATE = "state";
    const QString EMOJI = "emoji";
    const QString PARTY = "party";
    const QString ASSETS = "assets";
    const QString SECRETS = "secrets";
    const QString INSTANCE = "instance";
    const QString FLAGS = "flags";

public:
    QString name;
    int type;
    QString url;
    int created_at;
    QSharedPointer<Timestamps> timestamps;
    QString application_id;
    QString details;
    QString state;
    QSharedPointer<Emoji> emoji;
    QSharedPointer<Party> party;
    QSharedPointer<Assets> assets;
    QSharedPointer<Secrets> secrets;
    QSharedPointer<bool> instance;
    QSharedPointer<int> flags;

    void read(const QJsonObject &jsonObject) override {
        name = jsonObject[NAME].toString();
        type = jsonObject[TYPE].toInt();

        if (jsonObject.contains(URL)) {
            url = jsonObject[URL].toString();
        }

        created_at = jsonObject[CREATED_AT].toInt(0);

        if (jsonObject.contains(TIMESTAMPS)) {
            timestamps = QSharedPointer<Timestamps>(new Timestamps);
            timestamps->read(jsonObject[TIMESTAMPS].toObject());
        }

        if (jsonObject.contains(APPLICATION_ID)) {
            application_id = jsonObject[APPLICATION_ID].toString();
        }

        if (jsonObject.contains(DETAILS)) {
            details = jsonObject[DETAILS].toString();
        }

        if (jsonObject.contains(STATE)) {
            state = jsonObject[STATE].toString();
        }

        if (jsonObject.contains(EMOJI)) {
            emoji = QSharedPointer<Emoji>(new Emoji);
            emoji->read(jsonObject[EMOJI].toObject());
        }

        if (jsonObject.contains(PARTY)) {
            party = QSharedPointer<Party>(new Party);
            party->read(jsonObject[PARTY].toObject());
        }

        if (jsonObject.contains(ASSETS)) {
            assets = QSharedPointer<Assets>(new Assets);
            assets->read(jsonObject[ASSETS].toObject());
        }

        if (jsonObject.contains(SECRETS)) {
            secrets = QSharedPointer<Secrets>(new Secrets);
            secrets->read(jsonObject[SECRETS].toObject());
        }

        if (jsonObject.contains(INSTANCE)) {
            instance = QSharedPointer<bool>(new bool(jsonObject[INSTANCE].toBool()));
        }

        if (jsonObject.contains(FLAGS)) {
            flags = QSharedPointer<int>(new int(jsonObject[FLAGS].toInt()));
        }
    }


    /*
     * Note Bot can only send fields "name", "type", and "url"
     */
    void
    write(QJsonObject &jsonObject) const override {
        jsonObject[NAME] = name;
        jsonObject[TYPE] = type;

        if (!url.isEmpty()) {
            jsonObject[URL] = url;
        }
    }

    enum ActivityType {
        Game = 0,
        Streaming = 1,
        Listening = 2,
        Custom = 4
    };

    Q_ENUM(ActivityType)
};

#endif // ACTIVITY_H
