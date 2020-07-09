#include "embedauthor.h"

#include "util/serializationutils.h"


QJsonValue
EmbedAuthor::getName() const {
    return name;
}

void
EmbedAuthor::setName(const QJsonValue &value) {
    name = value;
}

QJsonValue
EmbedAuthor::getUrl() const {
    return url;
}

void
EmbedAuthor::setUrl(const QJsonValue &value) {
    url = value;
}

QJsonValue
EmbedAuthor::getIconUrl() const {
    return icon_url;
}

void
EmbedAuthor::setIconUrl(const QJsonValue &value) {
    icon_url = value;
}

QJsonValue
EmbedAuthor::getProxyIconUrl() const {
    return proxy_icon_url;
}

void
EmbedAuthor::setProxyIconUrl(const QJsonValue &value) {
    proxy_icon_url = value;
}

void
EmbedAuthor::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
EmbedAuthor::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
