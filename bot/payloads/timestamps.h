#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include "jsonserializeable.h"

#include <QSharedPointer>

class Timestamps : public JsonSerializeable
{
    const QString START = "start";
    const QString END = "end";
public:
    QSharedPointer<int> start;
    QSharedPointer<int> end;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // TIMESTAMPS_H
