#include "embedimage.h"

#include "util/jsonutils.h"


QJsonValue
EmbedImage::getUrl() const {
    return url;
}

void
EmbedImage::setUrl(const QJsonValue &value) {
    url = value;
}

QJsonValue
EmbedImage::getProxyUrl() const {
    return proxy_url;
}

void
EmbedImage::setProxyUrl(const QJsonValue &value) {
    proxy_url = value;
}

QJsonValue
EmbedImage::getHeight() const {
    return height;
}

void
EmbedImage::setHeight(const QJsonValue &value) {
    height = value;
}

QJsonValue
EmbedImage::getWidth() const {
    return width;
}

void
EmbedImage::setWidth(const QJsonValue &value) {
    width = value;
}

void
EmbedImage::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
EmbedImage::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
