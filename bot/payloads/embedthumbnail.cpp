#include "embedthumbnail.h"


const QString EmbedThumbnail::HEIGHT = "height";
const QString EmbedThumbnail::PROXY_URL = "proxy_url";
const QString EmbedThumbnail::URL = "url";
const QString EmbedThumbnail::WIDTH = "width";

QJsonValue
EmbedThumbnail::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedThumbnail::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedThumbnail::getProxyUrl() const {
    return _jsonObject[PROXY_URL];
}

void
EmbedThumbnail::setProxyUrl(const QJsonValue &proxyUrl) {
    _jsonObject[PROXY_URL] = proxyUrl;
}

QJsonValue
EmbedThumbnail::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
EmbedThumbnail::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
EmbedThumbnail::getWidth() const {
    return _jsonObject[WIDTH];
}

void
EmbedThumbnail::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}
