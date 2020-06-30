#include "identify.h"

#include "util/jsonutils.h"

QString
Identify::getToken() {
    return token;
}

void
Identify::setToken (QString token) {
    this->token = token;
}

QJsonObject
Identify::getProperties() {
    if (properties) {
        return properties->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Identify::setProperties(QJsonObject properties) {
    if (!properties.isEmpty()) {
        this->properties = QSharedPointer<IdentifyProperties>(new IdentifyProperties);
        JsonUtils::readFromJson(*this->properties, properties);
    }
}

QJsonValue
Identify::getCompress() {
    if (compress) {
        return QJsonValue(*compress);
    } else {
        return QJsonValue();
    }
}

void
Identify::setCompress(QJsonValue compress) {
    if (!compress.isNull()) {
        this->compress = QSharedPointer<bool>(new bool(compress.toBool()));
    }
}

QJsonValue
Identify::getLargeThreshold() {
    if (large_threshold) {
        return QJsonValue(*large_threshold);
    } else {
        return QJsonValue();
    }
}

void
Identify::setLargeThreshold(QJsonValue large_threshold) {
    if (!large_threshold.isNull()) {
        this->large_threshold = QSharedPointer<int>(new int(large_threshold.toInt()));
    }
}

QJsonArray
Identify::getShard() {
    if (shard[0] && shard[1]) {
        return QJsonArray { *shard[0], *shard[1] };
    } else {
        return QJsonArray();
    }
}

void
Identify::setShard(QJsonArray shard) {
    if (!shard.isEmpty()) {
        this->shard[0] = QSharedPointer<int>(new int(shard[0].toInt()));
        this->shard[1] = QSharedPointer<int>(new int(shard[1].toInt()));
    }
}

QJsonObject
Identify::getPresence() {
    if (presence) {
        return presence->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
Identify::setPresence(QJsonObject presence) {
    if (!this->presence) {
        this->presence = QSharedPointer<UpdateStatus>(new UpdateStatus);
    }
    JsonUtils::readFromJson(*this->presence, presence);
}

QJsonValue
Identify::getGuildSubscriptions() {
    if (guild_subscriptions) {
        return QJsonValue(*guild_subscriptions);
    } else {
        return QJsonValue();
    }
}

void
Identify::setGuildSubscriptions(QJsonValue guild_subscriptions) {
    if (!guild_subscriptions.isNull()) {
        this->guild_subscriptions = QSharedPointer<bool>(new bool(guild_subscriptions.toBool()));
    }
}

QJsonValue
Identify::getIntents() {
    if (intents) {
        return QJsonValue(*intents);
    } else {
        return QJsonValue();
    }
}

void
Identify::setIntents(QJsonValue intents) {
    if (!intents.isNull()) {
        this->intents = QSharedPointer<int>(new int(intents.toInt()));
    }
}

void
Identify::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
Identify::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
