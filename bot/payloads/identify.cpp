#include "identify.h"

const QString Identify::TOKEN = "token";
const QString Identify::PROPERTIES = "properties";
const QString Identify::COMPRESS = "compress";
const QString Identify::LARGE_THRESHOLD = "large_threshold";
const QString Identify::SHARD = "shard";
const QString Identify::PRESENCE = "presence";
const QString Identify::GUILD_SUBSCRIPTIONS = "guild_subscriptions";
const QString Identify::INTENTS = "intents";

QJsonValue
Identify::getToken() const {
    return _jsonObject[TOKEN];
}

void
Identify::setToken (const QJsonValue &token) {
    _jsonObject[TOKEN] = token;
}

QJsonObject
Identify::getProperties() const {
    return _jsonObject[PROPERTIES].toObject();
}

void
Identify::setProperties(const QJsonObject &properties) {
    _jsonObject[PROPERTIES] = properties;
}

QJsonValue
Identify::getCompress() const {
    return _jsonObject[COMPRESS];
}

void
Identify::setCompress(const QJsonValue &compress) {
    _jsonObject[COMPRESS] = compress;
}

QJsonValue
Identify::getLargeThreshold() const {
   return _jsonObject[LARGE_THRESHOLD];
}

void
Identify::setLargeThreshold(const QJsonValue &largeThreshold) {
    _jsonObject[LARGE_THRESHOLD] = largeThreshold;
}

QJsonArray
Identify::getShard() const {
    return _jsonObject[SHARD].toArray();
}

void
Identify::setShard(const QJsonArray &shard) {
    _jsonObject[SHARD] = shard;
}

QJsonObject
Identify::getPresence() const {
    return _jsonObject[PRESENCE].toObject();
}

void
Identify::setPresence(const QJsonObject &presence) {
    _jsonObject[PRESENCE] = presence;
}

QJsonValue
Identify::getGuildSubscriptions() const {
    return _jsonObject[GUILD_SUBSCRIPTIONS];
}

void
Identify::setGuildSubscriptions(const QJsonValue &guildSubscriptions) {
    _jsonObject[GUILD_SUBSCRIPTIONS] = guildSubscriptions;
}

QJsonValue
Identify::getIntents() const {
    return _jsonObject[INTENTS];
}

void
Identify::setIntents(const QJsonValue &intents) {
    _jsonObject[INTENTS] = intents;
}
