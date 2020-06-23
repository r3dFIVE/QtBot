#ifndef PRESENCE_H
#define PRESENCE_H

#include "activity.h"
#include "clientstatus.h"
#include "jsonserializable.h"
#include "user.h"


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

    QJsonObject
    getUser() {
        if (user) {
            return user->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setUser(QJsonObject user) {
        if (!user.isEmpty()) {
            this->user = QSharedPointer<User>(new User);
            JsonUtils::readFromJson(*this->user, user);
        }
    }

    QJsonArray
    getRoles() {
        QJsonArray roles;
        for (QString role : this->roles) {
            roles.push_back(role);
        }
        return roles;
    }

    void
    setRoles(QJsonArray roles) {
        for (QJsonValue roleId : roles) {
            this->roles.push_back(roleId.toString());
        }
    }

    QJsonObject
    getGame() {
        if (game) {
            return game->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setGame(QJsonObject game) {
        if (!game.isEmpty()) {
            this->game = QSharedPointer<Activity>(new Activity);
            JsonUtils::readFromJson(*this->game, game);
        }
    }

    QString
    getGuildId() {
        return guild_id;
    }

    void
    setGuildId(QString guild_id) {
        this->guild_id = guild_id;
    }

    QString
    getStatus() {
        return status;
    }

    void
    setStatus(QString status) {
        this->status = status;
    }

    QJsonArray
    getActivities() {
        QJsonArray activities;
        for (Activity activity : this->activities) {
            activities.push_back(activity.toQJsonObject());
        }
        return activities;
    }

    void
    setActivities(QJsonArray activities) {
        for (QJsonValue jsonValue : activities) {
            Activity activity;
            activity.fromQJsonObject(jsonValue.toObject());
            this->activities.push_back(activity);
        }
    }

    QJsonObject
    getClientStatus() {
        if (client_status) {
            return client_status->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setClientStatus(QJsonObject client_status) {
        if (!client_status.isEmpty()) {
            this->client_status = QSharedPointer<ClientStatus>(new ClientStatus);
            JsonUtils::readFromJson(*this->client_status, client_status);
        }
    }

    QString
    getPremiumSince() {
        return premium_since;
    }

    void
    setPremiumSince(QString premium_since) {
        this->premium_since = premium_since;
    }

    QString
    getNick() {
        return nick;
    }

    void
    setNick(QString nick) {
        this->nick = nick;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);

        if (!jsonObject.contains(GAME)) {
            jsonObject[GAME] = QJsonValue::Null;
        }
    }
};

Q_DECLARE_METATYPE(PresenceUpdate)

#endif // PRESENCE_H
