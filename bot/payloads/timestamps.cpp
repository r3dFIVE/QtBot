#include "timestamps.h"

void
Timestamps::read(const QJsonObject &jsonObject) {
    if (jsonObject.contains(START)) {
        start = QSharedPointer<int>(new int(jsonObject[START].toInt()));
    }

    if (jsonObject.contains(END)) {
        end = QSharedPointer<int>(new int(jsonObject[END].toInt()));
    }
}

void
Timestamps::write(QJsonObject &jsonObject) const {
    if (start != nullptr) {
        jsonObject[START] = *start;
    }

    if (end != nullptr) {
        jsonObject[END] = *end;
    }
}
