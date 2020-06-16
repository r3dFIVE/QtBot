#include "emoji.h"

void
Emoji::read(const QJsonObject &jsonObject) {
    name = jsonObject[NAME].toString();

    if (jsonObject.contains(ID)) {
        id = jsonObject[ID].toString();
    }

    if (jsonObject.contains(ANIMATED)) {
        animated = QSharedPointer<bool>(new bool(jsonObject[ANIMATED].toBool()));
    }
}

void
Emoji::write(QJsonObject &jsonObject) const {
    jsonObject[NAME] = name;

    if (!id.isEmpty()) {
        jsonObject[ID] = id;
    }

    if (animated != nullptr) {
        jsonObject[ANIMATED] = *animated;
    }
}
