#include "guildmember.h"


const QString GuildMember::USER = "user";
const QString GuildMember::NICK = "nick";
const QString GuildMember::ROLES = "roles";
const QString GuildMember::JOINED_AT = "joined_at";
const QString GuildMember::PREMIUM_SINCE = "premium_since";
const QString GuildMember::DEAF = "deaf";
const QString GuildMember::MUTE = "mute";

QJsonObject
GuildMember::getUser() const {
    return _jsonObject[USER].toObject();
}

void
GuildMember::setUser(const QJsonObject &user) {
    _jsonObject[USER] = user;
}

QJsonValue
GuildMember::getNick() const {
    return _jsonObject[NICK];
}

void
GuildMember::setNick(const QJsonValue &nick) {
    _jsonObject[NICK] = nick;
}

QJsonArray
GuildMember::getRoles() const {
    return _jsonObject[ROLES].toArray();
}

void
GuildMember::setRoles(const QJsonArray &roles) {
    _jsonObject[ROLES] = roles;
}

QJsonValue
GuildMember::getJoinedAt() const {
    return _jsonObject[JOINED_AT];
}

void
GuildMember::setJoinedAt(const QJsonValue &joinedAt) {
    _jsonObject[JOINED_AT] = joinedAt;
}

QJsonValue
GuildMember::getPremiumSince() const {
    return _jsonObject[PREMIUM_SINCE];
}

void
GuildMember::setPremiumSince(const QJsonValue &premiumSince) {
    _jsonObject[PREMIUM_SINCE] = premiumSince;
}

QJsonValue
GuildMember::getDeaf() const {
    return _jsonObject[DEAF];
}

void
GuildMember::setDeaf(const QJsonValue &deaf) {
    _jsonObject[DEAF] = deaf;
}

QJsonValue
GuildMember::getMute() const {
    return _jsonObject[MUTE];
}

void
GuildMember::setMute(const QJsonValue &mute) {
    _jsonObject[MUTE] = mute;
}
