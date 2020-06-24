#ifndef PRESENCE_H
#define PRESENCE_H

#include "activity.h"
#include "clientstatus.h"
#include "jsonserializable.h"
#include "user.h"

class Activity;
class User;

class PresenceUpdate : public JsonSerializable
{
    Q_OBJECT

public:
    const QString USER = "user";
    const QString ROLES = "roles";
    const QString GAME = "game";
    const QString GUILD_ID = "guild_id";
    const QString STATUS = "status";
    const QString ACTIVITIES = "activities";
    const QString CLIENT_STATUS = "client_status";
    const QString PREMIUM_SINCE = "premium_since";
    const QString NICK = "nick";

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    QSharedPointer<User> user;

    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    QList<QString> roles;

    Q_PROPERTY(QJsonObject game READ getGame WRITE setGame)
    QSharedPointer<Activity> game;

    Q_PROPERTY(QString guild_id READ getGuildId WRITE setGuildId)
    QString guild_id;

    Q_PROPERTY(QString status READ getStatus WRITE setStatus)
    QString status;

    Q_PROPERTY(QJsonArray activities READ getActivities WRITE setActivities)
    QList<Activity> activities;

    Q_PROPERTY(QJsonObject client_status READ getClientStatus WRITE setClientStatus)
    QSharedPointer<ClientStatus> client_status;

    Q_PROPERTY(QString premium_since READ getPremiumSince WRITE setPremiumSince)
    QString premium_since;

    Q_PROPERTY(QString nick READ getNick WRITE setNick)
    QString nick;

    QJsonObject getUser();
    void setUser(QJsonObject user);
    QJsonArray getRoles();
    void setRoles(QJsonArray roles);
    QJsonObject getGame();
    void setGame(QJsonObject game);
    QString getGuildId();
    void setGuildId(QString guild_id);
    QString getStatus();
    void setStatus(QString status);
    QJsonArray getActivities();
    void setActivities(QJsonArray activities);
    QJsonObject getClientStatus();
    void setClientStatus(QJsonObject client_status);
    QString getPremiumSince();
    void setPremiumSince(QString premium_since);
    QString getNick();
    void setNick(QString nick);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(PresenceUpdate)

#endif // PRESENCE_H
