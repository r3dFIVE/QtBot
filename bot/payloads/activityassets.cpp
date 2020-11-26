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

#include "activityassets.h"

const QString ActivityAssets::LARGE_IMAGE = "large_image";
const QString ActivityAssets::LARGE_TEXT = "large_text";
const QString ActivityAssets::SMALL_IMAGE = "small_image";
const QString ActivityAssets::SMALL_TEXT = "small_text";

QJsonValue
ActivityAssets::getLargeText() {
    return _jsonObject[LARGE_TEXT].toString();
}

void
ActivityAssets::setLargeText(const QJsonValue &largeText) {
    _jsonObject[LARGE_TEXT] = largeText;
}

QJsonValue
ActivityAssets::getSmallImage() {
    return _jsonObject[SMALL_IMAGE].toString();
}

void
ActivityAssets::setSmallImage(const QJsonValue &smallImage) {
    _jsonObject[SMALL_IMAGE] = smallImage;
}

QJsonValue
ActivityAssets::getSmallText() {
    return _jsonObject[SMALL_TEXT].toString();
}

void
ActivityAssets::setSmallText(const QJsonValue &smallText) {
    _jsonObject[SMALL_TEXT] = smallText;
}

QJsonValue
ActivityAssets::getLargeImage() {
    return _jsonObject[LARGE_IMAGE].toString();
}

void
ActivityAssets::setLargeImage(const QJsonValue &largeImage) {
    _jsonObject[LARGE_IMAGE] = largeImage;
}
