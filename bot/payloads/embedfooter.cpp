#include "embedfooter.h"


const QString EmbedFooter::ICON_URL = "icon_url";
const QString EmbedFooter::PROXY_ICON_URL = "proxy_icon_url";
const QString EmbedFooter::TEXT = "text";

QJsonValue
EmbedFooter::getText() const {
    return _jsonObject[TEXT];
}

void
EmbedFooter::setText(const QJsonValue &text) {
    _jsonObject[TEXT] = text;
}


QJsonValue
EmbedFooter::getIconUrl() const {
    return _jsonObject[ICON_URL];
}

void
EmbedFooter::setIconUrl(const QJsonValue &iconUrl) {
    _jsonObject[TEXT] = iconUrl;
}


QJsonValue
EmbedFooter::getProxyIconUrl() const {
    return _jsonObject[PROXY_ICON_URL];
}

void
EmbedFooter::setProxyIconUrl(const QJsonValue &proxyIconUrl) {
    _jsonObject[PROXY_ICON_URL] = proxyIconUrl;
}
