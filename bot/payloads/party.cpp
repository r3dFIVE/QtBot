#include "party.h"

#include <QJsonArray>

void
Party::read(const QJsonObject &jsonObject) {
    if (jsonObject.contains(ID)) {
        id = jsonObject[ID].toString();
    }

    if (jsonObject.contains(SIZE)) {
        QJsonArray jsonSize = jsonObject[SIZE].toArray(QJsonArray { 0, 0 });
        size[0] = QSharedPointer<int>(new int(jsonSize[0].toInt()));
        size[1] = QSharedPointer<int>(new int(jsonSize[1].toInt()));
    }
}

void
Party::write(QJsonObject &jsonObject) const {
    if (id.size() > 0) {
        jsonObject[ID] = id;
    }

    if (size[0] == nullptr || size[1] == nullptr) {
        jsonObject[SIZE] = QJsonArray{ *size[0], *size[1] };
    }
}
