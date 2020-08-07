#include "ready.h"

const QString Ready::V = "v";
const QString Ready::USER = "user";
const QString Ready::PRIVATE_CHANNELS = "private_channels";
const QString Ready::GUILDS = "guilds";
const QString Ready::SESSION_ID = "session_id";
const QString Ready::SHARD = "shard";

QJsonValue
Ready::getV() const {
    return _jsonObject[V];
}

void
Ready::setV(const QJsonValue &v) {
    _jsonObject[V] = v;
}

QJsonObject
Ready::getUser() const {
    return _jsonObject[USER].toObject();
}

void
Ready::setUser(const QJsonObject &user) {
    _jsonObject[USER] = user;
}

QJsonArray
Ready::getPrivateChannels() const {
    return _jsonObject[PRIVATE_CHANNELS].toArray();
}

void
Ready::setPrivateChannels(const QJsonArray &privateChannels) {
    _jsonObject[PRIVATE_CHANNELS] = privateChannels;
}

QJsonArray
Ready::getGuilds() const {
    return _jsonObject[GUILDS].toArray();
}

void
Ready::setGuilds(const QJsonArray &guilds) {
    _jsonObject[GUILDS] = guilds;
}

QJsonValue
Ready::getSessionId() const {
    return _jsonObject[SESSION_ID];
}

void
Ready::setSessionId(const QJsonValue &sessionId) {
   _jsonObject[SESSION_ID] = sessionId;
}

QJsonArray
Ready::getShard() const {
    return _jsonObject[SHARD].toArray();
}

void
Ready::setShard(const QJsonArray &shard) {
    _jsonObject[SHARD] = shard;
}
