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
