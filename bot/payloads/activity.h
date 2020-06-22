#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "jsonserializable.h"
#include "activitytimestamps.h"
#include "activityemoji.h"
#include "activityparty.h"
#include "activityassets.h"
#include "activitysecrets.h"

#include <QSharedPointer>

class Activity : public JsonSerializable
{
    Q_OBJECT

public:
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

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(int type READ getType WRITE setType)
    int type;

    Q_PROPERTY(QString url READ getUrl WRITE setUrl)
    QString url;

    Q_PROPERTY(int created_at READ getCreatedAt WRITE setCreatedAt)
    int created_at;

    Q_PROPERTY(QJsonObject timestamps  READ getTimestamps WRITE setTimestamps)
    QSharedPointer<ActivityTimestamps> timestamps;

    Q_PROPERTY(QString application_id READ getApplicationId WRITE setApplicationId)
    QString application_id;

    Q_PROPERTY(QString details READ getDetails WRITE setDetails)
    QString details;

    Q_PROPERTY(QString state READ getState WRITE setState)
    QString state;

    Q_PROPERTY(QJsonObject emoji READ getEmoji WRITE setEmoji)
    QSharedPointer<ActivityEmoji> emoji;

    Q_PROPERTY(QJsonObject party READ getParty WRITE setParty)
    QSharedPointer<ActivityParty> party;

    Q_PROPERTY(QJsonObject assets READ getAssets WRITE setAssets)
    QSharedPointer<ActivityAssets> assets;

    Q_PROPERTY(QJsonObject secrets READ getSecrets WRITE setSecrets)
    QSharedPointer<ActivitySecrets> secrets;

    Q_PROPERTY(QJsonValue instance READ getInstance WRITE setInstance)
    QSharedPointer<bool> instance;

    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
    QSharedPointer<int> flags;

    QString
    getName() {
        return name;
    }

    void
    setName(QString name) {
        this->name = name;
    }

    int
    getType() {
        return type;
    }

    void
    setType(int type) {
        this->type = type;
    }

    QString
    getUrl() {
        return url;
    }

    void
    setUrl(QString url) {
        this->url = url;
    }

    int
    getCreatedAt() {
        return created_at;
    }

    void
    setCreatedAt(int created_at) {
        this->created_at = created_at;
    }

    QJsonObject
    getTimestamps() {
        if (timestamps) {
            return timestamps->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setTimestamps(QJsonObject timestamps) {
        if (!this->timestamps) {
            this->timestamps = QSharedPointer<ActivityTimestamps>(new ActivityTimestamps);
        }
        JsonUtils::readFromJson(*this->timestamps, timestamps);
    }

    QString
    getApplicationId() {
        return application_id;
    }

    void
    setApplicationId(QString application_id) {
        this->application_id = application_id;
    }

    QString
    getDetails() {
        return details;
    }

    void
    setDetails(QString details) {
        this->details = details;
    }

    QString
    getState() {
        return state;
    }

    void
    setState(QString state) {
        this->state = state;
    }

    QJsonObject
    getEmoji() {
        if (emoji) {
            return emoji->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setEmoji(QJsonObject emoji) {
        if (!this->emoji) {
            this->emoji = QSharedPointer<ActivityEmoji>(new ActivityEmoji);
        }
        JsonUtils::readFromJson(*this->emoji, emoji);
    }

    QJsonObject
    getParty() {
        if (party) {
            return party->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setParty(QJsonObject party) {
        if (!this->party) {
            this->party = QSharedPointer<ActivityParty>(new ActivityParty);
        }
        JsonUtils::readFromJson(*this->party, party);
    }

    QJsonObject
    getAssets() {
        if (assets) {
            return assets->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setAssets(QJsonObject assets) {
        if (!this->assets) {
            this->assets = QSharedPointer<ActivityAssets>(new ActivityAssets);
        }
        JsonUtils::readFromJson(*this->assets, assets);
    }

    QJsonObject
    getSecrets() {
        if (secrets) {
            return secrets->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setSecrets(QJsonObject secrets) {
        if (!this->secrets) {
            this->secrets = QSharedPointer<ActivitySecrets>(new ActivitySecrets);
        }
        JsonUtils::readFromJson(*this->secrets, secrets);
    }

    QJsonValue
    getInstance() {
        if (instance) {
            return QJsonValue(*instance);
        }
        return QJsonValue();
    }

    void
    setInstance(QJsonValue instance) {
        if (!instance.isNull()) {
            this->instance = QSharedPointer<bool>(new bool(instance.toBool()));
        }
    }

    QJsonValue
    getFlags() {
        if (flags) {
            return QJsonValue(*flags);
        }
        return QJsonValue();
    }

    void
    setFlags(QJsonValue flags) {
        if (!flags.isNull()) {
            this->flags = QSharedPointer<int>(new int(flags.toInt()));
        }
    }

    void
    read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    /*
     * Note Bot can only send fields "name", "type", and "url"
     */
    void
    write(QJsonObject &jsonObject) override {
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

Q_DECLARE_METATYPE(Activity)

#endif // ACTIVITY_H
