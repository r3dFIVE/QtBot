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

#include "activitytimestamps.h"

const QString ActivityTimestamps::START = "start";
const QString ActivityTimestamps::END = "end";

QJsonValue
ActivityTimestamps::getStart() const {
    return _jsonObject[START];
}

void
ActivityTimestamps::setStart(const QJsonValue &start) {
     _jsonObject[START] = start;
}

QJsonValue
ActivityTimestamps::getEnd() const {
     return _jsonObject[END];
}

void
ActivityTimestamps::setEnd(const QJsonValue &end) {
     _jsonObject[END] = end;
}
