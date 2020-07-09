#include "activitytimestamps.h"

QJsonValue
ActivityTimestamps::getStart() {
    if (start) {
        return QJsonValue(*start);
    } else {
        return QJsonValue();
    }
}

void
ActivityTimestamps::setStart(QJsonValue start) {
    if (!start.isNull()) {
        this->start = QSharedPointer<int>(new int(start.toInt()));
    }
}

QJsonValue
ActivityTimestamps::getEnd() {
    if (end) {
        return QJsonValue(*end);
    } else {
        return QJsonValue();
    }
}

void
ActivityTimestamps::setEnd(QJsonValue end) {
    if (!end.isNull()) {
        this->end = QSharedPointer<int>(new int(end.toInt()));
    }
}

void
ActivityTimestamps::read(const QJsonObject &jsonObject)  {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
ActivityTimestamps::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
