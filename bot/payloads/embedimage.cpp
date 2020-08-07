#include "embedimage.h"


const QString EmbedImage::HEIGHT = "height";
const QString EmbedImage::PROXY_URL = "proxy_url";
const QString EmbedImage::URL = "url";
const QString EmbedImage::WIDTH = "width";

QJsonValue
EmbedImage::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedImage::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedImage::getProxyUrl() const {
    return _jsonObject[PROXY_URL];
}

void
EmbedImage::setProxyUrl(const QJsonValue &proxyUrl) {
    _jsonObject[PROXY_URL] = proxyUrl;
}

QJsonValue
EmbedImage::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
EmbedImage::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
EmbedImage::getWidth() const {
    return _jsonObject[WIDTH];
}

void
EmbedImage::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}
