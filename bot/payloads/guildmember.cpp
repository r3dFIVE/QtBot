#include "guildmember.h"
#include "util/serializationutils.h"

QJsonObject
GuildMember::getUser() {
    if (user) {
        return (user->toQJsonObject());
    } else {
        return QJsonObject();
    }
}

void
GuildMember::setUser(QJsonObject user) {
    if (!user.isEmpty()) {
        this->user = QSharedPointer<User>(new User);
        SerializationUtils::readFromJson(*this->user, user);
    }
}

QString
GuildMember::getNick() {
    return nick;
}

void
GuildMember::setNick(QString nick) {
    this->nick = nick;
}

QJsonArray
GuildMember::getRoles() {
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
GuildMember::setRoles(QJsonArray roles) {
    for (QJsonValue roleId : roles) {
        this->roles.push_back(roleId.toString());
    }
}

QString
GuildMember::getJoinedAt() {
    return joined_at;
}

void
GuildMember::setJoinedAt(QString joined_at) {
    this->joined_at = joined_at;
}

QString
GuildMember::getPremiumSince() {
    return premium_since;
}

void
GuildMember::setPremiumSince(QString premium_since) {
    this->premium_since = premium_since;
}

bool
GuildMember::getDeaf() {
    return deaf;
}

void
GuildMember::setDeaf(bool deaf) {
    this->deaf = deaf;
}

bool
GuildMember::getMute() {
    return mute;
}

void
GuildMember::setMute(bool mute) {
    this->mute = mute;
}

void
GuildMember::read(const QJsonObject &jsonObject) {
    SerializationUtils::readFromJson(*this, jsonObject);
}

void
GuildMember::write(QJsonObject &jsonObject) {
    SerializationUtils::writeToJson(*this, jsonObject);
}
