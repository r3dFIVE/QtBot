#include "embedprovider.h"

#include "util/jsonutils.h"


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
    JsonUtils::readFromJson(*this, jsonObject);
}

void
EmbedProvider::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
