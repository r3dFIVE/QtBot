#ifndef PRESENCE_H
#define PRESENCE_H

#include "activity.h"
#include "jsonserializeable.h"

#include <QSharedPointer>


class UpdateStatus : public JsonSerializeable
{
    const QString SINCE = "since";
    const QString GAME = "game";
    const QString STATUS = "status";
    const QString AFK = "afk";

public:
    QSharedPointer<int> since;
    QSharedPointer<Activity> game;
    QString status;
    bool afk;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};


#endif // PRESENCE_H
