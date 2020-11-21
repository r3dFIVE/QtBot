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
