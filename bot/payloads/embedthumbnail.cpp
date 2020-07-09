#include "embedthumbnail.h"

#include "util/serializationutils.h"


QJsonValue
EmbedThumbnail::getUrl() const {
    return url;
}

void
EmbedThumbnail::setUrl(const QJsonValue &value) {
    url = value;
}

QJsonValue
EmbedThumbnail::getProxyUrl() const {
    return proxy_url;
}

void
EmbedThumbnail::setProxyUrl(const QJsonValue &value) {
    proxy_url = value;
}

QJsonValue
EmbedThumbnail::getHeight() const {
    return height;
}

void
EmbedThumbnail::setHeight(const QJsonValue &value) {
    height = value;
}

QJsonValue
EmbedThumbnail::getWidth() const {
    return width;
}

void
EmbedThumbnail::setWidth(const QJsonValue &value) {
    width = value;
}

void
EmbedThumbnail::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
EmbedThumbnail::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
