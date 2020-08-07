#include "attachment.h"

const QString Attachment::ID = "id";
const QString Attachment::FILENAME = "filename";
const QString Attachment::SIZE = "size";
const QString Attachment::URL = "url";
const QString Attachment::PROXY_URL = "proxy_url";
const QString Attachment::HEIGHT = "height";
const QString Attachment::WIDTH = "width";

QJsonValue
Attachment::getId() {
    return _jsonObject[ID];
}

void
Attachment::setId(QJsonValue id) {
    _jsonObject[ID] = id;
}

QJsonValue
Attachment::getFilename() {
    return _jsonObject[FILENAME];
}

void
Attachment::setFilename(QJsonValue filename) {
    _jsonObject[FILENAME] = filename;
}

QJsonValue
Attachment::getSize() {
    return _jsonObject[SIZE];
}

void
Attachment::setSize(QJsonValue size) {
    _jsonObject[SIZE] = size;
}

QJsonValue
Attachment::getUrl() {
    return _jsonObject[URL];
}

void
Attachment::setUrl(QJsonValue url) {
    _jsonObject[URL] = url;
}

QJsonValue
Attachment::getProxyUrl() {
    return _jsonObject[PROXY_URL];
}

void
Attachment::setProxyUrl(QJsonValue proxy_url) {
    _jsonObject[PROXY_URL] = proxy_url;
}

QJsonValue
Attachment::getHeight() {
    return _jsonObject[HEIGHT];
}

void
Attachment::setHeight(QJsonValue height) {
    _jsonObject[HEIGHT] = height;
}

QJsonValue
Attachment::getWidth() {
    return _jsonObject[WIDTH];
}

void
Attachment::setWidth(QJsonValue width) {
    _jsonObject[WIDTH] = width;
}
