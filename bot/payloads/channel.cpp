#include "channel.h"

#include <jsonutils.h>

QString
Channel::getId() {
    return id;
}

void
Channel::setId(QString id) {
    this->id = id;
}

int
Channel::getType() {
    return type;
}

void
Channel::setType(int type) {
    this->type = type;
}

QString
Channel::getGuildId() {
    return guild_id;
}

void
Channel::setGuildId(QString guild_id) {
    this->guild_id = guild_id;
}

QJsonValue
Channel::getPosition() {
    if (position) {
        return *position;
    }
    return QJsonValue();
}

void
Channel::setPosition(QJsonValue position) {
    if (!position.isNull()) {
        this->position = QSharedPointer<int>(new int(position.toInt()));
    }
}

QJsonArray
Channel::getPermissionOverwrites() {
    QJsonArray permission_overwrites;
    for (PermissionOverwrite po : this->permission_overwrites) {
        QJsonObject permissionOverwrite = po.toQJsonObject();
        permission_overwrites.push_back(permissionOverwrite);
    }
    return permission_overwrites;
}

void
Channel::setPermissionOverwrites(QJsonArray permission_overwrites) {
    for (QJsonValue jsonObject : permission_overwrites) {
        PermissionOverwrite permissionOverwrite;
        permissionOverwrite.fromQJsonObject(jsonObject.toObject());
        this->permission_overwrites.push_back(permissionOverwrite);
    }
}

QString
Channel::getName() {
    return name;
}

void
Channel::setName(QString name) {
    this->name = name;
}

QString
Channel::getTopic() {
    return topic;
}

void
Channel::setTopic(QString topic) {
    this->topic = topic;
}

QJsonValue
Channel::getNsfw() {
    if (nsfw) {
        return *nsfw;
    }
    return QJsonValue();
}

void
Channel::setNsfw(QJsonValue nsfw) {
    if (!nsfw.isNull()) {
        this->nsfw = QSharedPointer<bool>(new bool(nsfw.toBool()));
    }
}

QString
Channel::getLastMessageId() {
    return last_message_id;
}

void
Channel::setLastMessageId(QString last_message_id) {
    this->last_message_id = last_message_id;
}

QJsonValue
Channel::getBitrate() {
    if (bitrate) {
        return *bitrate;
    }
    return QJsonValue();
}

void
Channel::setBitrate(QJsonValue bitrate) {
    if (!bitrate.isNull()) {
        this->bitrate = QSharedPointer<int>(new int(bitrate.toInt()));
    }
}

QJsonValue
Channel::getUserLimit() {
    if (user_limit) {
        return *user_limit;
    }
    return QJsonValue();
}

void
Channel::setUserLimit(QJsonValue user_limit) {
    if (!user_limit.isNull()) {
        this->user_limit = QSharedPointer<int>(new int(user_limit.toInt()));
    }
}

QJsonValue
Channel::getRateLimitPerUser() {
    if (rate_limit_per_user) {
        return *rate_limit_per_user;
    }
    return QJsonValue();
}

void
Channel::setRateLimitPerUser(QJsonValue rate_limit_per_user) {
    if (!rate_limit_per_user.isNull()) {
        this->rate_limit_per_user = QSharedPointer<int>(new int(rate_limit_per_user.toInt()));
    }
}

QJsonArray
Channel::getRecipients() {
    QJsonArray recipients;
    for (User u : this->recipients) {
        QJsonObject user = u.toQJsonObject();
        recipients.push_back(user);
    }
    return recipients;
}

void
Channel::setRecipients(QJsonArray recipients) {
    for (QJsonValue jsonValue : recipients) {
        User recipient;
        recipient.fromQJsonObject(jsonValue.toObject());
        this->recipients.push_back(recipient);
    }
}

QString
Channel::getIcon() {
    return icon;
}

void
Channel::setIcon(QString icon) {
    this->icon = icon;
}

QString
Channel::getOwnerId() {
    return owner_id;
}

void
Channel::setOwnerId(QString owner_id) {
    this->owner_id = owner_id;
}

QString
Channel::getApplicationId() {
    return application_id;
}

void
Channel::setApplicationId(QString application_id) {
    this->application_id = application_id;
}

QString
Channel::getParentId() {
    return parent_id;
}

void
Channel::setParentId(QString parent_id) {
    this->parent_id = parent_id;
}

QString
Channel::getLastPinTimestamp() {
    return last_pin_timestamp;
}

void
Channel::setLastPinTimestamp(QString last_pin_timestamp) {
    this->last_pin_timestamp = last_pin_timestamp;
}

void
Channel::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
Channel::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
