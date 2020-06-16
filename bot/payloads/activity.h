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

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;

    enum ActivityType {
        Game = 0,
        Streaming = 1,
        Listening = 2,
        Custom = 4
    };

    Q_ENUM(ActivityType)
};

#endif // ACTIVITY_H
