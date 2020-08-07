#ifndef CHANNEL_H
#define CHANNEL_H

#include "jsonserializable.h"


class Channel : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString TYPE;
    static const QString GUILD_ID;
    static const QString POSITION;
    static const QString PERMISSION_OVERWRITES ;
    static const QString NAME;
    static const QString TOPIC;
    static const QString NSFW;
    static const QString LAST_MESSAGE_ID;
    static const QString BITRATE;
    static const QString USER_LIMIT;
    static const QString RATE_LIMIT_PER_USER;
    static const QString RECIPIENTS;
    static const QString ICON;
    static const QString OWNER_ID;
    static const QString APPLICATION_ID;
    static const QString PARENT_ID;
    static const QString LAST_PIN_TIMESTAMP;

    Channel() {}
    Channel(const QByteArray &json) : JsonSerializable(json) {}
    Channel(const QJsonObject &json) : JsonSerializable(json) {}
    Channel(const QString &json) : JsonSerializable(json) {}

    QJsonValue getApplicationId();
    QJsonValue getBitrate();
    QJsonValue getGuildId();
    QJsonValue getIcon();
    QJsonValue getId();
    QJsonValue getLastMessageId();
    QJsonValue getLastPinTimestamp();
    QJsonValue getOwnerId();
    QJsonValue getName();
    QJsonValue getNsfw();
    QJsonValue getParentId();
    QJsonValue getPosition();
    QJsonValue getRateLimitPerUser();
    QJsonValue getTopic();
    QJsonValue getType();
    QJsonValue getUserLimit();
    QJsonArray getRecipients();
    QJsonArray getPermissionOverwrites();
    void setId(const QJsonValue &id);
    void setType(const QJsonValue &type);
    void setGuildId(const QJsonValue &guildId);
    void setPosition(const QJsonValue &position);
    void setPermissionOverwrites(const QJsonArray &permissionOverwrites);
    void setName(const QJsonValue &name);
    void setTopic(const QJsonValue &topic);
    void setNsfw(const QJsonValue &nsfw);
    void setLastMessageId(const QJsonValue &lastMessageId);
    void setBitrate(const QJsonValue &bitrate);
    void setUserLimit(const QJsonValue &userLimit);
    void setRateLimitPerUser(const QJsonValue &rateLimitPerUser);
    void setRecipients(const QJsonArray &recipients);
    void setIcon(const QJsonValue &icon);
    void setOwnerId(const QJsonValue &ownerId);
    void setApplicationId(const QJsonValue &applicationId);
    void  setParentId(const QJsonValue &parentId);
    void setLastPinTimestamp(const QJsonValue &lastPinTimestamp);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue type READ getType WRITE setType)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue position READ getPosition WRITE setPosition)
    Q_PROPERTY(QJsonArray permission_overwrites READ getPermissionOverwrites WRITE setPermissionOverwrites)
    Q_PROPERTY(QJsonValue name READ getName WRITE setName)
    Q_PROPERTY(QJsonValue topic READ getTopic WRITE setTopic)
    Q_PROPERTY(QJsonValue nsfw READ getNsfw WRITE setNsfw)
    Q_PROPERTY(QJsonValue last_message_id READ getLastMessageId WRITE setLastMessageId)
    Q_PROPERTY(QJsonValue bitrate READ getBitrate WRITE setBitrate)
    Q_PROPERTY(QJsonValue user_limit READ getUserLimit WRITE setUserLimit)
    Q_PROPERTY(QJsonValue rate_limit_per_user READ getRateLimitPerUser WRITE setRateLimitPerUser)
    Q_PROPERTY(QJsonArray recipients READ getRecipients WRITE setRecipients)
    Q_PROPERTY(QJsonValue icon READ getIcon WRITE setIcon)
    Q_PROPERTY(QJsonValue owner_id READ getOwnerId WRITE setOwnerId)
    Q_PROPERTY(QJsonValue application_id READ getApplicationId WRITE setApplicationId)
    Q_PROPERTY(QJsonValue parent_id READ getParentId WRITE setParentId)
    Q_PROPERTY(QJsonValue last_pin_timestamp READ getLastPinTimestamp WRITE setLastPinTimestamp)
};

Q_DECLARE_METATYPE(Channel)

#endif // CHANNEL_H
