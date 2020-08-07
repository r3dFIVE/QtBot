#include "embedvideo.h"


const QString EmbedVideo::HEIGHT = "height";
const QString EmbedVideo::URL = "url";
const QString EmbedVideo::WIDTH = "width";

QJsonValue
EmbedVideo::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedVideo::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedVideo::getHeight() const {
    return _jsonObject[HEIGHT];
}

void
EmbedVideo::setHeight(const QJsonValue &height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
EmbedVideo::getWidth() const {
    return _jsonObject[WIDTH];
}

void
EmbedVideo::setWidth(const QJsonValue &width) {
    _jsonObject[WIDTH] = width;
}
