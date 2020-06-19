#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "identifyproperties.h"
#include "jsonserializeable.h"
#include "updatestatus.h"

#include <QSharedPointer>
#include <QJsonArray>

class Identify : public JsonSerializeable
{

    Q_OBJECT
public:
    const QString TOKEN = "token";
    const QString PROPERTIES = "properties";
    const QString COMPRESS = "compress";
    const QString LARGE_THRESHOLD = "large_threshold";
    const QString SHARD = "shard";
    const QString PRESENCE = "presence";
    const QString GUILD_SUBSCRIPTIONS = "guild_subscriptions";
    const QString INTENTS = "intents";

    Q_PROPERTY(QString token READ getToken WRITE setToken)
    QString token;

    Q_PROPERTY(QJsonObject properties READ getProperties WRITE setProperties)
    QSharedPointer<IdentifyProperties> properties;

    Q_PROPERTY(QJsonValue compress READ getCompress WRITE setCompress)
    QSharedPointer<bool> compress;

    Q_PROPERTY(QJsonValue large_threshold READ getLargeThreshold WRITE setLargeThreshold)
    QSharedPointer<int> large_threshold;

    Q_PROPERTY(QJsonArray shard READ getShard WRITE setShard)
    QSharedPointer<int> shard[2];

    Q_PROPERTY(QJsonObject presence READ getPresence WRITE setPresence)
    QSharedPointer<UpdateStatus> presence;

    Q_PROPERTY(QJsonValue guild_subscriptions READ getGuildSubscriptions WRITE setGuildSubscriptions)
    QSharedPointer<bool> guild_subscriptions;

    Q_PROPERTY(QJsonValue intents READ getIntents WRITE setIntents)
    QSharedPointer<int> intents;

    QString
    getToken() {
        return token;
    }

    void
    setToken (QString token) {
        this->token = token;
    }

    QJsonObject
    getProperties() {
        if (properties) {
            return properties->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setProperties(QJsonObject properties) {
        if (!this->properties) {
            this->properties = QSharedPointer<IdentifyProperties>();
        }
        JsonUtils::readFromJson(*this->properties, properties);
    }

    QJsonValue
    getCompress() {
        if (compress) {
            return QJsonValue(*compress);
        } else {
            return QJsonValue();
        }
    }

    void
    setCompress(QJsonValue compress) {
        if (!compress.isNull()) {
            this->compress = QSharedPointer<bool>(new bool(compress.toBool()));
        }
    }

    QJsonValue
    getLargeThreshold() {
        if (large_threshold) {
            return QJsonValue(*large_threshold);
        } else {
            return QJsonValue();
        }
    }

    void
    setLargeThreshold(QJsonValue large_threshold) {
        if (!large_threshold.isNull()) {
            this->large_threshold = QSharedPointer<int>(new int(large_threshold.toInt()));
        }
    }

    QJsonArray
    getShard() {
        if (shard[0] && shard[1]) {
            return QJsonArray { *shard[0], *shard[1] };
        } else {
            return QJsonArray();
        }
    }

    void
    setShard(QJsonArray shard) {
        if (!shard.isEmpty()) {
            this->shard[0] = QSharedPointer<int>(new int(shard[0].toInt()));
            this->shard[1] = QSharedPointer<int>(new int(shard[1].toInt()));
        }
    }

    QJsonObject
    getPresence() {
        if (presence) {
            return presence->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setPresence(QJsonObject presence) {
        if (!this->presence) {
            this->presence = QSharedPointer<UpdateStatus>(new UpdateStatus);
        }
        JsonUtils::readFromJson(*this->presence, presence);
    }

    QJsonValue
    getGuildSubscriptions() {
        if (guild_subscriptions) {
            return QJsonValue(*guild_subscriptions);
        } else {
            return QJsonValue();
        }
    }

    void
    setGuildSubscriptions(QJsonValue guild_subscriptions) {
        if (!guild_subscriptions.isNull()) {
            this->guild_subscriptions = QSharedPointer<bool>(new bool(guild_subscriptions.toBool()));
        }
    }

    QJsonValue
    getIntents() {
        if (intents) {
            return QJsonValue(*intents);
        } else {
            return QJsonValue();
        }
    }

    void
    setIntents(QJsonValue intents) {
        if (!intents.isNull()) {
            this->intents = QSharedPointer<int>(new int(intents.toInt()));
        }
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

Q_DECLARE_METATYPE(Identify)

#endif // IDENTIFY_H
