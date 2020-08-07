#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include "jsonserializable.h"


class ActivityTimestamps : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString START;
    static const QString END;

    ActivityTimestamps() {}
    ActivityTimestamps(const QByteArray &json) : JsonSerializable(json) {}
    ActivityTimestamps(const QJsonObject &json) : JsonSerializable(json) {}
    ActivityTimestamps(const QString &json) : JsonSerializable(json) {}

    void setEnd(const QJsonValue &end);
    void setStart(const QJsonValue &start);
    QJsonValue getEnd() const;
    QJsonValue getStart() const;

    Q_PROPERTY(QJsonValue start READ getStart WRITE setStart)
    Q_PROPERTY(QJsonValue end READ getEnd WRITE setEnd)
};

Q_DECLARE_METATYPE(ActivityTimestamps)

#endif // TIMESTAMPS_H
