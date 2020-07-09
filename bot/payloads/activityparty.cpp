#include "activityparty.h"

#include <util/serializationutils.h>

QString
ActivityParty::getId() {
    return id;
}

void
ActivityParty::setId(QString id) {
    this->id = id;
}

QJsonArray
ActivityParty::getSize() {
    if (size[0] && size[1]) {
        return QJsonArray { *size[0], *size[1] };
    } else {
        return QJsonArray();
    }
}

void
ActivityParty::setSize(QJsonArray size) {
    if (!size.isEmpty()) {
        this->size[0] = QSharedPointer<int>(new int(size[0].toInt()));
        this->size[1] = QSharedPointer<int>(new int(size[1].toInt()));
    }
}

void
ActivityParty::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
ActivityParty::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
