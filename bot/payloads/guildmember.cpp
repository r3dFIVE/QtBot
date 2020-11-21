/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
