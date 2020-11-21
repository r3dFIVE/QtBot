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

#include "resume.h"


const QString Resume::TOKEN = "token";
const QString Resume::SESSION_ID = "session_id";
const QString Resume::SEQ = "seq";

QJsonValue
Resume::getToken() const {
    return _jsonObject[TOKEN];
}

void
Resume::setToken(const QJsonValue &token) {
    _jsonObject[TOKEN] = token;
}

QJsonValue
Resume::getSessionId() const {
    return _jsonObject[SESSION_ID];
}

void
Resume::setSessionId(const QJsonValue &sessionId) {
    _jsonObject[SESSION_ID] = sessionId;
}

QJsonValue
Resume::getSeq() const {
    return _jsonObject[SEQ];
}

void
Resume::setSeq(const QJsonValue &seq) {
    _jsonObject[SEQ] = seq;
}
