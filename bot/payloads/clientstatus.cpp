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

#include "clientstatus.h"

const QString ClientStatus::DESKTOP = "desktop";
const QString ClientStatus::MOBILE = "mobile";
const QString ClientStatus::WEB = "web";

QJsonValue
ClientStatus::getDesktop() const {
    return _jsonObject[DESKTOP];
}

void
ClientStatus::setDesktop(const QJsonValue &desktop) {
    _jsonObject[DESKTOP] = desktop;
}

QJsonValue
ClientStatus::getMobile() const {
    return _jsonObject[MOBILE];
}

void
ClientStatus::setMobile(const QJsonValue &mobile) {
    _jsonObject[MOBILE] = mobile;
}

QJsonValue
ClientStatus::getWeb() const {
    return _jsonObject[WEB];
}

void
ClientStatus::setWeb(const QJsonValue &web) {
    _jsonObject[WEB] = web;
}
