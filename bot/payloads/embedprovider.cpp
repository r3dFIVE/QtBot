#include "embedprovider.h"

#include "util/serializationutils.h"


QJsonValue
EmbedProvider::getUrl() const {
    return url;
}

void
EmbedProvider::setUrl(const QJsonValue &value) {
    url = value;
}

QJsonValue
EmbedProvider::getName() const {
    return name;
}

void
EmbedProvider::setName(const QJsonValue &value) {
    name = value;
}

void
EmbedProvider::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
EmbedProvider::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
