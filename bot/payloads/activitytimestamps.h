#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include "jsonserializeable.h"

#include <QSharedPointer>

class ActivityTimestamps : public JsonSerializeable
{
    Q_OBJECT

public:
    const QString START = "start";
    const QString END = "end";

    Q_PROPERTY(QJsonValue start READ getStart WRITE setStart)
    QSharedPointer<int> start;

    Q_PROPERTY(QJsonValue end READ getEnd WRITE setEnd)
    QSharedPointer<int> end;

    QJsonValue
    getStart() {
        if (start) {
            return QJsonValue(*start);
        } else {
            return QJsonValue();
        }
    }

    void
    setStart(QJsonValue start) {
        if (!start.isNull()) {
            this->start = QSharedPointer<int>(new int(start.toInt()));
        }
    }

    QJsonValue
    getEnd() {
        if (end) {
            return QJsonValue(*end);
        } else {
            return QJsonValue();
        }
    }

    void
    setEnd(QJsonValue end) {
        if (!end.isNull()) {
            this->end = QSharedPointer<int>(new int(end.toInt()));
        }
    }

    void
    read(const QJsonObject &jsonObject) override  {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void
    write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(ActivityTimestamps)

#endif // TIMESTAMPS_H
