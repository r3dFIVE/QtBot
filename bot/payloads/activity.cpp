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

#include "activity.h"

const QString Activity::NAME = "name";
const QString Activity::TYPE = "type";
const QString Activity::URL = "url";
const QString Activity::CREATED_AT = "created_at";
const QString Activity::TIMESTAMPS = "timestamps";
const QString Activity::APPLICATION_ID = "application_id";
const QString Activity::DETAILS = "details";
const QString Activity::STATE = "state";
const QString Activity::EMOJI = "emoji";
const QString Activity::PARTY = "party";
const QString Activity::ASSETS = "assets";
const QString Activity::SECRETS = "secrets";
const QString Activity::INSTANCE = "instance";
const QString Activity::FLAGS = "flags";

QJsonValue
Activity::getName() const {
    return _jsonObject[NAME];
}

void
Activity::setName(const QJsonValue &name) {
   _jsonObject[NAME] = name;
}

QJsonValue
Activity::getType() const {
    return _jsonObject[TYPE];
}

void
Activity::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonValue
Activity::getUrl() const {
    return _jsonObject[URL];
}

void
Activity::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
Activity::getCreatedAt() const {
    return _jsonObject[CREATED_AT];
}

void
Activity::setCreatedAt(const QJsonValue &created_at) {
    _jsonObject[CREATED_AT] = created_at;
}

QJsonObject
Activity::getTimestamps() const {
    return _jsonObject[TIMESTAMPS].toObject();
}

void
Activity::setTimestamps(const QJsonObject &timestamps) {
    _jsonObject[TIMESTAMPS] = timestamps;
}

QJsonValue
Activity::getApplicationId() const {
    return _jsonObject[APPLICATION_ID];
}

void
Activity::setApplicationId(const QJsonValue &application_id) {
    _jsonObject[APPLICATION_ID] = application_id;
}

QJsonValue
Activity::getDetails() const {
    return _jsonObject[DETAILS];
}

void
Activity::setDetails(const QJsonValue &details) {
    _jsonObject[DETAILS] = details;
}

QJsonValue
Activity::getState() const {
    return _jsonObject[STATE];
}

void
Activity::setState(const QJsonValue &state) {
    _jsonObject[STATE] = state;
}

QJsonObject
Activity::getEmoji() const {
    return _jsonObject[EMOJI].toObject();
}

void
Activity::setEmoji(const QJsonObject &emoji) {
    _jsonObject[EMOJI] = emoji;
}

QJsonObject
Activity::getParty() const {
    return _jsonObject[PARTY].toObject();
}

void
Activity::setParty(const QJsonObject &party) {
    _jsonObject[PARTY] = party;
}

QJsonObject
Activity::getAssets() const {
    return _jsonObject[ASSETS].toObject();
}

void
Activity::setAssets(const QJsonObject &assets) {
    _jsonObject[ASSETS] = assets;
}

QJsonObject
Activity::getSecrets() const {
    return _jsonObject[SECRETS].toObject();
}

void
Activity::setSecrets(const QJsonObject &secrets) {
    _jsonObject[SECRETS] = secrets;
}

QJsonValue
Activity::getInstance() const {
    return _jsonObject[INSTANCE];
}

void
Activity::setInstance(const QJsonValue &instance) {
     _jsonObject[INSTANCE] = instance;
}

QJsonValue
Activity::getFlags() const {
    return _jsonObject[FLAGS];
}

void
Activity::setFlags(const QJsonValue &flags) {
    _jsonObject[FLAGS] = flags;
}
