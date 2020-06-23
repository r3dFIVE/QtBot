#ifndef CHANNEL_H
#define CHANNEL_H

#include "jsonserializable.h"
#include "permissionoverwrite.h"
#include "user.h"


class Channel : public JsonSerializable
{
    Q_OBJECT

public:
    const QString ID = "id";
    const QString TYPE = "type";
    const QString GUILD_ID = "guild_id";
    const QString POSITION = "position";
    const QString PERMISSION_OVERWRITES = "permission_overwrites" ;
    const QString NAME = "name";
    const QString TOPIC = "topic";
    const QString NSFW = "nsfw";
    const QString LAST_MESSAGE_ID = "last_message_id";
    const QString BITRATE = "bitrate";
    const QString USER_LIMIT = "user_limit";
    const QString RATE_LIMIT_PER_USER = "rate_limit_per_user";
    const QString RECIPIENTS = "recipients";
    const QString ICON = "icon";
    const QString OWNER_ID = "owner_id";
    const QString APPLICATION_ID = "application_id";
    const QString PARENT_ID = "parent_id";
    const QString LAST_PIN_TIMESTAMP = "last_pin_timestamp";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(int type READ getType WRITE setType)
    int type;

    Q_PROPERTY(QString guild_id READ getGuildId WRITE setGuildId)
    QString guild_id;

    Q_PROPERTY(QJsonValue position READ getPosition WRITE setPosition)
    QSharedPointer<int> position;

    Q_PROPERTY(QJsonArray permission_overwrites READ getPermissionOverwrites WRITE setPermissionOverwrites)
    QList<PermissionOverwrite> permission_overwrites;

    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;

    Q_PROPERTY(QString topic READ getTopic WRITE setTopic)
    QString topic;

    Q_PROPERTY(QJsonValue nsfw READ getNsfw WRITE setNsfw)
    QSharedPointer<bool> nsfw;

    Q_PROPERTY(QString last_message_id READ getLastMessageId WRITE setLastMessageId)
    QString last_message_id;

    Q_PROPERTY(QJsonValue bitrate READ getBitrate WRITE setBitrate)
    QSharedPointer<int> bitrate;

    Q_PROPERTY(QJsonValue user_limit READ getUserLimit WRITE setUserLimit)
    QSharedPointer<int> user_limit;

    Q_PROPERTY(QJsonValue rate_limit_per_user READ getRateLimitPerUser WRITE setRateLimitPerUser)
    QSharedPointer<int> rate_limit_per_user;

    Q_PROPERTY(QJsonArray recipients READ getRecipients WRITE setRecipients)
    QList<User> recipients;

    Q_PROPERTY(QString icon READ getIcon WRITE setIcon)
    QString icon;

    Q_PROPERTY(QString owner_id READ getOwnerId WRITE setOwnerId)
    QString owner_id;

    Q_PROPERTY(QString application_id READ getApplicationId WRITE setApplicationId)
    QString application_id;

    Q_PROPERTY(QString parent_id READ getParentId WRITE setParentId)
    QString parent_id;

    Q_PROPERTY(QString last_pin_timestamp READ getLastPinTimestamp WRITE setLastPinTimestamp)
    QString last_pin_timestamp;

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    int
    getType() {
        return type;
    }

    void
    setType(int type) {
        this->type = type;
    }

    QString
    getGuildId() {
        return guild_id;
    }

    void
    setGuildId(QString guild_id) {
        this->guild_id = guild_id;
    }

    QJsonValue
    getPosition() {
        if (position) {
            return *position;
        }
        return QJsonValue();
    }

    void
    setPosition(QJsonValue position) {
        if (!position.isNull()) {
            this->position = QSharedPointer<int>(new int(position.toInt()));
        }
    }

    QJsonArray
    getPermissionOverwrites() {
        QJsonArray permission_overwrites;
        for (PermissionOverwrite po : this->permission_overwrites) {
            QJsonObject permissionOverwrite = po.toQJsonObject();
            permission_overwrites.push_back(permissionOverwrite);
        }
        return permission_overwrites;
    }

    void
    setPermissionOverwrites(QJsonArray permission_overwrites) {
        for (QJsonValue jsonObject : permission_overwrites) {
            PermissionOverwrite permissionOverwrite;
            permissionOverwrite.fromQJsonObject(jsonObject.toObject());
            this->permission_overwrites.push_back(permissionOverwrite);
        }
    }

    QString
    getName() {
        return name;
    }

    void
    setName(QString name) {
        this->name = name;
    }

    QString
    getTopic() {
        return topic;
    }

    void
    setTopic(QString topic) {
        this->topic = topic;
    }

    QJsonValue
    getNsfw() {
        if (nsfw) {
            return *nsfw;
        }
        return QJsonValue();
    }

    void
    setNsfw(QJsonValue nsfw) {
        if (!nsfw.isNull()) {
            this->nsfw = QSharedPointer<bool>(new bool(nsfw.toBool()));
        }
    }

    QString
    getLastMessageId() {
        return last_message_id;
    }

    void
    setLastMessageId(QString last_message_id) {
        this->last_message_id = last_message_id;
    }

    QJsonValue
    getBitrate() {
        if (bitrate) {
            return *bitrate;
        }
        return QJsonValue();
    }

    void
    setBitrate(QJsonValue bitrate) {
        if (!bitrate.isNull()) {
            this->bitrate = QSharedPointer<int>(new int(bitrate.toInt()));
        }
    }

    QJsonValue
    getUserLimit() {
        if (user_limit) {
            return *user_limit;
        }
        return QJsonValue();
    }

    void
    setUserLimit(QJsonValue user_limit) {
        if (!user_limit.isNull()) {
            this->user_limit = QSharedPointer<int>(new int(user_limit.toInt()));
        }
    }

    QJsonValue
    getRateLimitPerUser() {
        if (rate_limit_per_user) {
            return *rate_limit_per_user;
        }
        return QJsonValue();
    }

    void
    setRateLimitPerUser(QJsonValue rate_limit_per_user) {
        if (!rate_limit_per_user.isNull()) {
            this->rate_limit_per_user = QSharedPointer<int>(new int(rate_limit_per_user.toInt()));
        }
    }

    QJsonArray
    getRecipients() {        
        QJsonArray recipients;
        for (User u : this->recipients) {
            QJsonObject user = u.toQJsonObject();
            recipients.push_back(user);
        }
        return recipients;
    }

    void
    setRecipients(QJsonArray recipients) {
        for (QJsonValue jsonValue : recipients) {
            User recipient;
            recipient.fromQJsonObject(jsonValue.toObject());
            this->recipients.push_back(recipient);
        }
    }

    QString
    getIcon() {
        return icon;
    }

    void
    setIcon(QString icon) {
        this->icon = icon;
    }

    QString
    getOwnerId() {
        return owner_id;
    }

    void
    setOwnerId(QString owner_id) {
        this->owner_id = owner_id;
    }

    QString
    getApplicationId() {
        return application_id;
    }

    void
    setApplicationId(QString application_id) {
        this->application_id = application_id;
    }

    QString
    getParentId() {
        return parent_id;
    }

    void
    setParentId(QString parent_id) {
        this->parent_id = parent_id;
    }

    QString
    getLastPinTimestamp() {
        return last_pin_timestamp;
    }

    void
    setLastPinTimestamp(QString last_pin_timestamp) {
        this->last_pin_timestamp = last_pin_timestamp;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(Channel)

#endif // CHANNEL_H
