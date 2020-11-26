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

#include "identifyproperties.h"


const QString IdentifyProperties::OS = "$os";
const QString IdentifyProperties::BROWSER = "$browser";
const QString IdentifyProperties::DEVICE = "$device";

IdentifyProperties::IdentifyProperties() {
    _jsonObject[OS] = $os;
    _jsonObject[BROWSER] = $browser;
    _jsonObject[DEVICE] = $device;
}

QJsonValue
IdentifyProperties::getOS() const {
    return _jsonObject[OS];
}

QJsonValue
IdentifyProperties::getBrowser() const {
    return _jsonObject[BROWSER];
}

QJsonValue
IdentifyProperties::getDevice() const {
    return _jsonObject[BROWSER];
}

void
IdentifyProperties::setBrowser(const QJsonValue &browser) {
    _jsonObject[BROWSER] = browser;
}

void
IdentifyProperties::setDevice(const QJsonValue &device) {
    _jsonObject[DEVICE] = device;
}

void
IdentifyProperties::setOS(const QJsonValue &os) {
    _jsonObject[OS] = os;
}

