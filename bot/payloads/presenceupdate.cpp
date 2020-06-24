#include "presenceupdate.h"

#include <jsonutils.h>

QJsonObject
PresenceUpdate::getUser() {
    if (user) {
        return user->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
PresenceUpdate::setUser(QJsonObject user) {
    if (!user.isEmpty()) {
        this->user = QSharedPointer<User>(new User);
        JsonUtils::readFromJson(*this->user, user);
    }
}

QJsonArray
PresenceUpdate::getRoles() {
    QJsonArray roles;
    for (QString role : this->roles) {
        roles.push_back(role);
    }
    return roles;
}

void
PresenceUpdate::setRoles(QJsonArray roles) {
    for (QJsonValue roleId : roles) {
        this->roles.push_back(roleId.toString());
    }
}

QJsonObject
PresenceUpdate::getGame() {
    if (game) {
        return game->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
PresenceUpdate::setGame(QJsonObject game) {
    if (!game.isEmpty()) {
        this->game = QSharedPointer<Activity>(new Activity);
        JsonUtils::readFromJson(*this->game, game);
    }
}

QString
PresenceUpdate::getGuildId() {
    return guild_id;
}

void
PresenceUpdate::setGuildId(QString guild_id) {
    this->guild_id = guild_id;
}

QString
PresenceUpdate::getStatus() {
    return status;
}

void
PresenceUpdate::setStatus(QString status) {
    this->status = status;
}

QJsonArray
PresenceUpdate::getActivities() {
    QJsonArray activities;
    for (Activity activity : this->activities) {
        activities.push_back(activity.toQJsonObject());
    }
    return activities;
}

void
PresenceUpdate::setActivities(QJsonArray activities) {
    for (QJsonValue jsonValue : activities) {
        Activity activity;
        activity.fromQJsonObject(jsonValue.toObject());
        this->activities.push_back(activity);
    }
}

QJsonObject
PresenceUpdate::getClientStatus() {
    if (client_status) {
        return client_status->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
PresenceUpdate::setClientStatus(QJsonObject client_status) {
    if (!client_status.isEmpty()) {
        this->client_status = QSharedPointer<ClientStatus>(new ClientStatus);
        JsonUtils::readFromJson(*this->client_status, client_status);
    }
}

QString
PresenceUpdate::getPremiumSince() {
    return premium_since;
}

void
PresenceUpdate::setPremiumSince(QString premium_since) {
    this->premium_since = premium_since;
}

QString
PresenceUpdate::getNick() {
    return nick;
}

void
PresenceUpdate::setNick(QString nick) {
    this->nick = nick;
}

void
PresenceUpdate::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);

    if (!jsonObject.contains(GAME)) {
        jsonObject[GAME] = QJsonValue::Null;
    }
}

void
PresenceUpdate::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

