#include "ready.h"

#include "util/jsonutils.h"

int
Ready::getV() {
    return v;
}

void
Ready::setV(int v) {
    this->v = v;
}

QJsonObject
Ready::getUser() {
    return user.toQJsonObject();
}

void
Ready::setUser(QJsonObject user) {
    if (!user.isEmpty()) {
        this->user.fromQJsonObject(user);
    }
}

QJsonArray
Ready::getPrivateChannels() {
    QJsonArray private_channels;
    for (Channel channel : this->private_channels) {
        private_channels.push_back(channel.toQJsonObject());
    }
    return private_channels;
}

void
Ready::setPrivateChannels(QJsonArray private_channels) {
    for (QJsonValue jsonValue : private_channels) {
        Channel channel;
        channel.fromQJsonObject(jsonValue.toObject());
        this->private_channels.push_back(channel);
    }
}

QJsonArray
Ready::getGuilds() {
    QJsonArray guilds;
    for (Guild guild : this->guilds) {
        guilds.push_back(guild.toQJsonObject());
    }
    return guilds;
}

void
Ready::setGuilds(QJsonArray guilds) {
    for (QJsonValue jsonValue : guilds) {
        Guild guild;
        guild.fromQJsonObject(jsonValue.toObject());
        this->guilds.push_back(guild);
    }
}

QString
Ready::getSessionId() {
    return session_id;
}

void
Ready::setSessionId(QString session_id) {
   this->session_id = session_id;
}

QJsonArray
Ready::getShard() {
    if (shard[0] && shard[1]) {
        return QJsonArray { *shard[0], *shard[1] };
    } else {
        return QJsonArray();
    }
}

void
Ready::setShard(QJsonArray shard) {
    if (!shard.isEmpty()) {
        this->shard[0] = QSharedPointer<int>(new int(shard[0].toInt()));
        this->shard[1] = QSharedPointer<int>(new int(shard[1].toInt()));
    }
}

void
Ready::read(const QJsonObject &jsonObject)  {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
Ready::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
