#include "embedprovider.h"


const QString EmbedProvider::NAME = "name";
const QString EmbedProvider::URL = "url";

QJsonValue
EmbedProvider::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedProvider::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedProvider::getName() const {
    return _jsonObject[NAME];
}

void
EmbedProvider::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}
