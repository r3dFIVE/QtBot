#ifndef EMOJI_H
#define EMOJI_H

#include "jsonserializeable.h"

#include <QSharedPointer>


class Emoji : public JsonSerializeable
{

public:
    const QString NAME = "name";
    const QString ID = "id";
    const QString ANIMATED = "animated";

    QString name;
    QString id;
    QSharedPointer<bool> animated;

    void read(const QJsonObject &jsonObject) override {
        name = jsonObject[NAME].toString();

        if (jsonObject.contains(ID)) {
            id = jsonObject[ID].toString();
        }

        if (jsonObject.contains(ANIMATED)) {
            animated = QSharedPointer<bool>(new bool(jsonObject[ANIMATED].toBool()));
        }
    }

    void write(QJsonObject &jsonObject) const override {
        jsonObject[NAME] = name;

        if (!id.isEmpty()) {
            jsonObject[ID] = id;
        }

        if (animated != nullptr) {
            jsonObject[ANIMATED] = *animated;
        }
    }
};

#endif // EMOJI_H
