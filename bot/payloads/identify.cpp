#include "identify.h"

#include <QJsonArray>

void
Identify::read(const QJsonObject &jsonObject) {
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

void
Identify::write(QJsonObject &jsonObject) const {
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
