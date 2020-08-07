#include "presenceupdate.h"


const QString PresenceUpdate::USER = "user";
const QString PresenceUpdate::ROLES = "roles";
const QString PresenceUpdate::GAME = "game";
const QString PresenceUpdate::GUILD_ID = "guild_id";
const QString PresenceUpdate::STATUS = "status";
const QString PresenceUpdate::ACTIVITIES = "activities";
const QString PresenceUpdate::CLIENT_STATUS = "client_status";
const QString PresenceUpdate::PREMIUM_SINCE = "premium_since";
const QString PresenceUpdate::NICK = "nick";

QJsonObject
PresenceUpdate::getUser() const {
    return _jsonObject[USER].toObject();
}

void
PresenceUpdate::setUser(const QJsonObject &user) {
    _jsonObject[USER] = user;
}

QJsonArray
PresenceUpdate::getRoles() const {
    return _jsonObject[ROLES].toArray();
}

void
PresenceUpdate::setRoles(const QJsonArray &roles) {
    _jsonObject[ROLES] = roles;
}

QJsonObject
PresenceUpdate::getGame() const {
    return _jsonObject[GAME].toObject();
}

void
PresenceUpdate::setGame(const QJsonObject &game) {
    _jsonObject[GAME] = game;
}

QJsonValue
PresenceUpdate::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
PresenceUpdate::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonValue
PresenceUpdate::getStatus() const {
    return _jsonObject[STATUS];
}

void
PresenceUpdate::setStatus(const QJsonValue &status) {
    _jsonObject[STATUS] = status;
}

QJsonArray
PresenceUpdate::getActivities() const {
    return _jsonObject[ACTIVITIES].toArray();
}

void
PresenceUpdate::setActivities(const QJsonArray &activities) {
    _jsonObject[ACTIVITIES] = activities;
}

QJsonObject
PresenceUpdate::getClientStatus() const {
    return _jsonObject[CLIENT_STATUS].toObject();
}

void
PresenceUpdate::setClientStatus(const QJsonObject &clientStatus) {
    _jsonObject[CLIENT_STATUS] = clientStatus;
}

QJsonValue
PresenceUpdate::getPremiumSince() const {
    return _jsonObject[PREMIUM_SINCE];
}

void
PresenceUpdate::setPremiumSince(const QJsonValue &premiumSince) {
    _jsonObject[PREMIUM_SINCE] = premiumSince;
}

QJsonValue
PresenceUpdate::getNick() const {
    return _jsonObject[NICK];
}

void
PresenceUpdate::setNick(const QJsonValue &nick) {
    _jsonObject[NICK] = nick;
}
