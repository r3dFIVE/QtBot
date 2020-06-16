#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include "jsonserializeable.h"

#include <QSharedPointer>

class Timestamps : public JsonSerializeable
{
public:
    const QString START = "start";
    const QString END = "end";

    QSharedPointer<int> start;
    QSharedPointer<int> end;

    void read(const QJsonObject &jsonObject) override  {
        if (jsonObject.contains(START)) {
            start = QSharedPointer<int>(new int(jsonObject[START].toInt()));
        }

        if (jsonObject.contains(END)) {
            end = QSharedPointer<int>(new int(jsonObject[END].toInt()));
        }
    }

    void write(QJsonObject &jsonObject) const override {
        if (start != nullptr) {
            jsonObject[START] = *start;
        }

        if (end != nullptr) {
            jsonObject[END] = *end;
        }
    }
};

#endif // TIMESTAMPS_H
