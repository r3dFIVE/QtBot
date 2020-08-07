#ifndef PRESENCE_H
#define PRESENCE_H

#include "jsonserializable.h"


class UpdateStatus : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString AFK;
    static const QString GAME;
    static const QString SINCE;
    static const QString STATUS;

    UpdateStatus() {}
    UpdateStatus(const QByteArray &json) : JsonSerializable(json) {}
    UpdateStatus(const QJsonObject &json) : JsonSerializable(json) {}
    UpdateStatus(const QString &json) : JsonSerializable(json) {}

    QJsonObject getGame() const;
    QJsonValue getAfk() const;
    QJsonValue getSince() const;
    QJsonValue getStatus() const;
    void setAfk(const QJsonValue &afk);
    void setGame(const QJsonObject &game);
    void setStatus(const QJsonValue &status);
    void setSince(const QJsonValue &since);

    Q_PROPERTY(QJsonValue since READ getSince WRITE setSince)
    Q_PROPERTY(QJsonObject game READ getGame WRITE setGame)
    Q_PROPERTY(QJsonValue status READ getStatus WRITE setStatus)
    Q_PROPERTY(QJsonValue afk READ getAfk WRITE setAfk)
};

Q_DECLARE_METATYPE(UpdateStatus)

#endif // PRESENCE_H
