#ifndef PARTY_H
#define PARTY_H

#include "jsonserializeable.h"

#include <QSharedPointer>
#include <QJsonArray>

class Party : public JsonSerializeable
{
    const QString ID = "id";
    const QString SIZE = "size";

public:
    QString id;
    QSharedPointer<int> size[2];

    void read(const QJsonObject &jsonObject) override {
        if (jsonObject.contains(ID)) {
            id = jsonObject[ID].toString();
        }

        if (jsonObject.contains(SIZE)) {
            QJsonArray jsonSize = jsonObject[SIZE].toArray(QJsonArray { 0, 0 });
            size[0] = QSharedPointer<int>(new int(jsonSize[0].toInt()));
            size[1] = QSharedPointer<int>(new int(jsonSize[1].toInt()));
        }
    }

    void write(QJsonObject &jsonObject) const override  {
        if (id.size() > 0) {
            jsonObject[ID] = id;
        }

        if (size[0] == nullptr || size[1] == nullptr) {
            jsonObject[SIZE] = QJsonArray{ *size[0], *size[1] };
        }
    }
};

#endif // PARTY_H
