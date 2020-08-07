#include "embedfield.h"

const QString EmbedField::INLINE = "inline";
const QString EmbedField::NAME = "name";
const QString EmbedField::VALUE = "value";

QJsonValue
EmbedField::getValue() const {
    return _jsonObject[VALUE];
}

void
EmbedField::setValue(const QJsonValue &value) {
    _jsonObject[VALUE] = value;
}

QJsonValue
EmbedField::getInline() const {
    return _jsonObject[INLINE];
}

void
EmbedField::setInline(const QJsonValue &inln) {
    _jsonObject[INLINE] = inln;
}

QJsonValue
EmbedField::getName() const {
    return _jsonObject[NAME];
}

void EmbedField::setName(const QJsonValue &name) {
    _jsonObject[NAME] = name;
}
