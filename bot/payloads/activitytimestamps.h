#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include "jsonserializable.h"

#include <QSharedPointer>
#include <util/serializationutils.h>

class ActivityTimestamps : public JsonSerializable
{
    Q_OBJECT

public:
    const QString START = "start";
    const QString END = "end";

    Q_PROPERTY(QJsonValue start READ getStart WRITE setStart)
    QSharedPointer<int> start;

    Q_PROPERTY(QJsonValue end READ getEnd WRITE setEnd)
    QSharedPointer<int> end;

    QJsonValue getStart();
    void setStart(QJsonValue start);
    QJsonValue getEnd();
    void setEnd(QJsonValue end);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(ActivityTimestamps)

#endif // TIMESTAMPS_H
