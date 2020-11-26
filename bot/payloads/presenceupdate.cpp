/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
