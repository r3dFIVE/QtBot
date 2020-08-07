#include "embedauthor.h"

const QString EmbedAuthor::ICON_URL = "icon_url";
const QString EmbedAuthor::NAME = "name";
const QString EmbedAuthor::PROXY_ICON_URL = "proxy_icon_url";
const QString EmbedAuthor::URL = "url";

QJsonValue
EmbedAuthor::getName() const {
    return _jsonObject[NAME];
}

void
EmbedAuthor::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}

QJsonValue
EmbedAuthor::getUrl() const {
    return _jsonObject[URL];
}

void
EmbedAuthor::setUrl(const QJsonValue &url) {
    _jsonObject[URL] = url;
}

QJsonValue
EmbedAuthor::getIconUrl() const {
    return _jsonObject[ICON_URL];
}

void
EmbedAuthor::setIconUrl(const QJsonValue &iconUrl) {
    _jsonObject[ICON_URL] = iconUrl;
}

QJsonValue
EmbedAuthor::getProxyIconUrl() const {
    return _jsonObject[PROXY_ICON_URL];
}

void
EmbedAuthor::setProxyIconUrl(const QJsonValue &proxyIconUrl) {
    _jsonObject[PROXY_ICON_URL] = proxyIconUrl;
}
