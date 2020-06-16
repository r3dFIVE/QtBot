#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "properties.h"
#include "jsonserializeable.h"
#include "updatestatus.h"

#include <QSharedPointer>
#include <QJsonArray>

class Identify : public JsonSerializeable
{
    const QString TOKEN = "token";
    const QString PROPERTIES = "properties";
    const QString COMPRESS = "compress";
    const QString LARGE_THRESHOLD = "large_threshold";
    const QString SHARD = "shard";
    const QString PRESENCE = "presence";
    const QString GUILD_SUBSCRIPTIONS = "guild_subscriptions";
    const QString INTENTS = "intents";

public:
    QString token;
    Properties properties;
    QSharedPointer<bool> compress;
    QSharedPointer<int> large_threshold;
    QSharedPointer<int> shard[2];
    QSharedPointer<UpdateStatus> presence;
    QSharedPointer<bool> guild_subscriptions;
    QSharedPointer<int> intents;

    void read(const QJsonObject &jsonObject) override {
        token = jsonObject[TOKEN].toString();
        properties.fromQJsonObject(jsonObject[PROPERTIES].toObject());

        if (jsonObject.contains(COMPRESS)) {
            compress = QSharedPointer<bool>(new bool(jsonObject[COMPRESS].toBool()));
        }

        if (jsonObject.contains(LARGE_THRESHOLD)) {
            large_threshold = QSharedPointer<int>(new int(jsonObject[LARGE_THRESHOLD].toInt()));
        }

        if (jsonObject.contains(SHARD)) {
            QJsonArray jsonShard = jsonObject[SHARD].toArray();
            shard[0] = QSharedPointer<int>(new int(jsonShard[0].toInt()));
            shard[1] = QSharedPointer<int>(new int(jsonShard[1].toInt()));
        }

        if (jsonObject.contains(PRESENCE)) {
            presence = QSharedPointer<UpdateStatus>(new UpdateStatus);
            presence->read(jsonObject[PRESENCE].toObject());
        }

        if (jsonObject.contains(GUILD_SUBSCRIPTIONS)) {
            guild_subscriptions = QSharedPointer<bool>(new bool(jsonObject[GUILD_SUBSCRIPTIONS].toBool()));
        }

        if (jsonObject.contains(INTENTS)) {
            intents = QSharedPointer<int>(new int(jsonObject[INTENTS].toInt()));
        }
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject[TOKEN] = token;
        jsonObject[PROPERTIES] = properties.toQJsonObject();

        if (compress != nullptr) {
            jsonObject[COMPRESS] = *compress;
        }

        if (large_threshold != nullptr) {
            jsonObject[LARGE_THRESHOLD] = *large_threshold;
        }

        if (shard[0] != nullptr && shard[1] != nullptr) {
            jsonObject[SHARD] = QJsonArray { *shard[0], *shard[1] };
        }

        if (presence != nullptr) {
            jsonObject[PRESENCE] = presence->toQJsonObject();
        }

        if (guild_subscriptions != nullptr) {
            jsonObject[GUILD_SUBSCRIPTIONS] = *guild_subscriptions;
        }

        if (intents != nullptr) {
            jsonObject[INTENTS] = *intents;
        }
    }
};

#endif // IDENTIFY_H
