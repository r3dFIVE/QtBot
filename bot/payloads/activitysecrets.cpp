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

#include "activitysecrets.h"

const QString ActivitySecrets::JOIN = "join";
const QString ActivitySecrets::MATCH = "match";
const QString ActivitySecrets::SPECTATE = "spectate";

QJsonValue
ActivitySecrets::getJoin() {
    return _jsonObject[JOIN].toString();
}

void
ActivitySecrets::setJoin(const QJsonValue &join) {
   _jsonObject[JOIN] = join;
}

QJsonValue
ActivitySecrets::getSpectate() {
    return _jsonObject[SPECTATE].toString();
}

void
ActivitySecrets::setSpectate(const QJsonValue &spectate) {
   _jsonObject[SPECTATE] = spectate;
}

QJsonValue
ActivitySecrets::getMatch() {
    return _jsonObject[MATCH].toString();
}

void
ActivitySecrets::setMatch(const QJsonValue &match) {
    _jsonObject[MATCH] = match;
}


