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

#include "ready.h"

const QString Ready::V = "v";
const QString Ready::USER = "user";
const QString Ready::PRIVATE_CHANNELS = "private_channels";
const QString Ready::GUILDS = "guilds";
const QString Ready::SESSION_ID = "session_id";
const QString Ready::SHARD = "shard";
const QString Ready::RESUME_GATEWAY_URL = "resume_gateway_url";

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

QJsonValue
Ready::getResumeGatewayUrl() const {
    return _jsonObject[RESUME_GATEWAY_URL].toString();
}

