#include "embedfield.h"

#include "util/jsonutils.h"


QJsonValue
EmbedField::getValue() const {
    return value;
}

void
EmbedField::setValue(const QJsonValue &value) {
    this->value = value;
}

QJsonValue
EmbedField::getInline() const {
    return inln;
}

void
EmbedField::setInline(const QJsonValue &value) {
    inln = value;
}

QJsonValue
EmbedField::getName() const {
    return name;
}

void EmbedField::setName(const QJsonValue &value) {
    name = value;
}

void
EmbedField::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
EmbedField::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
