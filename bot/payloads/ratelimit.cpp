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

#include "ratelimit.h"


const QString RateLimit::GLOBAL = "global";
const QString RateLimit::MESSAGE = "message";
const QString RateLimit::RETRY_AFTER = "retry_after";

QJsonValue
RateLimit::getGlobal() const {
    return _jsonObject[GLOBAL];
}

void
RateLimit::setGlobal(const QJsonValue &global) {
    _jsonObject[GLOBAL] = global;
}

QJsonValue
RateLimit::getMessage() const {
    return _jsonObject[MESSAGE];
}

void
RateLimit::setMessage(const QJsonValue &message) {
    _jsonObject[MESSAGE] = message;
}

QJsonValue
RateLimit::getRetryAfter() const {
    return _jsonObject[RETRY_AFTER];
}

void
RateLimit::setRetryAfter(const QJsonValue &retryAfter) {
    _jsonObject[RETRY_AFTER] = retryAfter;
}
