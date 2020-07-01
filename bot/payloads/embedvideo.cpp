#include "embedvideo.h"

#include "util/jsonutils.h"


QJsonValue
EmbedVideo::getUrl() const {
    return url;
}

void
EmbedVideo::setUrl(const QJsonValue &value) {
    url = value;
}

QJsonValue
EmbedVideo::getHeight() const {
    return height;
}

void
EmbedVideo::setHeight(const QJsonValue &value) {
    height = value;
}

QJsonValue
EmbedVideo::getWidth() const {
    return width;
}

void
EmbedVideo::setWidth(const QJsonValue &value) {
    width = value;
}

void
EmbedVideo::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
EmbedVideo::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
