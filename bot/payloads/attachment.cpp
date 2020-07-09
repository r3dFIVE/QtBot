#include "attachment.h"
#include "util/serializationutils.h"

QJsonValue
Attachment::getId() {
    return id;
}

void
Attachment::setId(QJsonValue id) {
    this->id = id;
}

QJsonValue
Attachment::getFilename() {
    return filename;
}

void
Attachment::setFilename(QJsonValue filename) {
    this->filename = filename;
}

QJsonValue
Attachment::getSize() {
    return size;
}

void
Attachment::setSize(QJsonValue size) {
    this->size = size;
}

QJsonValue
Attachment::getUrl() {
    return url;
}

void
Attachment::setUrl(QJsonValue url) {
    this->url = url;
}

QJsonValue
Attachment::getProxyUrl() {
    return proxy_url;
}

void
Attachment::setProxyUrl(QJsonValue proxy_url) {
    this->proxy_url = proxy_url;
}

QJsonValue
Attachment::getHeight() {
    return height;
}

void
Attachment::setHeight(QJsonValue height) {
    this->height = height;
}

QJsonValue
Attachment::getWidth() {
    return width;
}

void
Attachment::setWidth(QJsonValue width) {
    this->width = width;
}

void
Attachment::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
Attachment::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
