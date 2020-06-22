#ifndef GUILDMEMBER_H
#define GUILDMEMBER_H

#include "jsonserializable.h"
#include "user.h"


class GuildMember : public JsonSerializable
{
    Q_OBJECT

public:
    const QString USER = "user";
    const QString NICK = "nick";
    const QString ROLES = "roles";
    const QString JOINED_AT = "joined_at";
    const QString PREMIUM_SINCE = "premium_since";
    const QString DEAF = "deaf";
    const QString MUTE = "mute";

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    QSharedPointer<User> user;

    Q_PROPERTY(QString nick READ getNick WRITE setNick)
    QString nick;

    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    QList<QString> roles;

    Q_PROPERTY(QString joined_at READ getJoinedAt WRITE setJoinedAt)
    QString joined_at;

    Q_PROPERTY(QString premium_since READ getPremiumSince WRITE setPremiumSince)
    QString premium_since;

    Q_PROPERTY(bool deaf READ getDeaf WRITE setDeaf)
    bool deaf;

    Q_PROPERTY(bool mute READ getMute WRITE setDeaf)
    bool mute;

    QJsonObject
    getUser() {
        if (user) {
            return (user->toQJsonObject());
        } else {
            return QJsonObject();
        }
    }

    void
    setUser(QJsonObject user) {
        if (!user.isEmpty()) {
            if (!this->user) {
                this->user = QSharedPointer<User>(new User);
            }
            JsonUtils::readFromJson(*this->user, user);
        }
    }

    QString
    getNick() {
        return nick;
    }

    void
    setNick(QString nick) {
        this->nick = nick;
    }

    QJsonArray
    getRoles() {
        if (roles.isEmpty()) {
            return QJsonArray();
        } else {
            QJsonArray roles;
            for (QString roleId : this->roles) {
                roles.push_back(roleId);
            }
            return roles;
        }
    }

    void
    setRoles(QJsonArray roles) {
        for (QJsonValue roleId : roles) {
            this->roles.push_back(roleId.toString());
        }
    }

    QString
    getJoinedAt() {
        return joined_at;
    }

    void
    setJoinedAt(QString joined_at) {
        this->joined_at = joined_at;
    }

    QString
    getPremiumSince() {
        return premium_since;
    }

    void
    setPremiumSince(QString premium_since) {
        this->premium_since = premium_since;
    }

    bool
    getDeaf() {
        return deaf;
    }

    void
    setDeaf(bool deaf) {
        this->deaf = deaf;
    }

    bool
    getMute() {
        return mute;
    }

    void
    setMute(bool mute) {
        this->mute = mute;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(GuildMember)

#endif // GUILDMEMBER_H
