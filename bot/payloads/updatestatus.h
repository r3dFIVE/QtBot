#ifndef PRESENCE_H
#define PRESENCE_H

#include "activity.h"
#include "jsonserializable.h"

#include <QSharedPointer>


class UpdateStatus : public JsonSerializable
{
    Q_OBJECT

public:
    const QString SINCE = "since";
    const QString GAME = "game";
    const QString STATUS = "status";
    const QString AFK = "afk";

    Q_PROPERTY(QJsonValue since READ getSince WRITE setSince)
    QSharedPointer<int> since;

    Q_PROPERTY(QJsonObject game READ getGame WRITE setGame)
    QSharedPointer<Activity> game;

    Q_PROPERTY(QString status READ getStatus WRITE setStatus)
    QString status;

    Q_PROPERTY(bool afk READ getAfk WRITE setAfk)
    bool afk;

    QJsonValue getSince();
    void setSince(QJsonValue since);
    QJsonObject getGame();
    void setGame(QJsonObject game);
    QString getStatus();
    void setStatus(QString status);
    bool getAfk();
    void setAfk(bool afk);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(UpdateStatus)

#endif // PRESENCE_H
