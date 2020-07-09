#include "embedfooter.h"

#include "util/serializationutils.h"

QJsonValue
EmbedFooter::getText() const {
    return text;
}

void
EmbedFooter::setText(const QJsonValue &value) {
    text = value;
}


QJsonValue
EmbedFooter::getIconUrl() const {
    return icon_url;
}

void
EmbedFooter::setIconUrl(const QJsonValue &value) {
    icon_url = value;
}


QJsonValue
EmbedFooter::getProxyIconUrl() const {
    return proxy_icon_url;
}

void
EmbedFooter::setProxyIconUrl(const QJsonValue &value) {
    proxy_icon_url = value;
}

void
EmbedFooter::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
EmbedFooter::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);

}
