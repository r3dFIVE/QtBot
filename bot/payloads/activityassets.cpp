#include "activityassets.h"

#include <jsonutils.h>

QString
ActivityAssets::getLargeText() {
    return large_text;
}

void
ActivityAssets::setLargeText(QString &value) {
    large_text = value;
}
QString
ActivityAssets::getSmallImage() {
    return small_image;
}

void
ActivityAssets::setSmallImage(QString &value) {
    small_image = value;
}

QString
ActivityAssets::getSmallText() {
    return small_text;
}

void
ActivityAssets::setSmallText(QString &value) {
    small_text = value;
}

QString
ActivityAssets::getLargeImage() {
    return large_image;
}

void
ActivityAssets::setLargeImage(QString &value) {
    large_image = value;
}

void
ActivityAssets::read(const QJsonObject &jsonObject)  {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
ActivityAssets::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
