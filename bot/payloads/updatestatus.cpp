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

#include "updatestatus.h"


const QString UpdateStatus::SINCE = "since";
const QString UpdateStatus::GAME = "game";
const QString UpdateStatus::STATUS = "status";
const QString UpdateStatus::AFK = "afk";

QJsonValue
UpdateStatus::getSince() const {
    return _jsonObject[SINCE];
}

void
UpdateStatus::setSince(const QJsonValue &since) {
    _jsonObject[SINCE] = since;
}

QJsonObject
UpdateStatus::getGame() const {
    return _jsonObject[GAME].toObject();
}

void
UpdateStatus::setGame(const QJsonObject &game) {
    _jsonObject[GAME] = game;
}

QJsonValue
UpdateStatus::getStatus() const {
    return _jsonObject[STATUS];
}

void
UpdateStatus::setStatus(const QJsonValue &status) {
    _jsonObject[STATUS] = status;
}

QJsonValue
UpdateStatus::getAfk() const {
    return _jsonObject[AFK];
}

void
UpdateStatus::setAfk(const QJsonValue &afk) {
    _jsonObject[AFK] = afk;
}
