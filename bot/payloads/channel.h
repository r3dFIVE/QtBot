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

    QString getId();
    void setId(QString id);
    int getType();
    void setType(int type);
    QString getGuildId();
    void setGuildId(QString guild_id);
    QJsonValue getPosition();
    void setPosition(QJsonValue position);
    QJsonArray getPermissionOverwrites();
    void setPermissionOverwrites(QJsonArray permission_overwrites);
    QString getName();
    void setName(QString name);
    QString getTopic();
    void setTopic(QString topic);
    QJsonValue getNsfw();
    void setNsfw(QJsonValue nsfw);
    QString getLastMessageId();
    void setLastMessageId(QString last_message_id);
    QJsonValue getBitrate();
    void setBitrate(QJsonValue bitrate);
    QJsonValue getUserLimit();
    void setUserLimit(QJsonValue user_limit);
    QJsonValue getRateLimitPerUser();
    void setRateLimitPerUser(QJsonValue rate_limit_per_user);
    QJsonArray getRecipients();
    void setRecipients(QJsonArray recipients);
    QString getIcon();
    void setIcon(QString icon);
    QString getOwnerId();
    void setOwnerId(QString owner_id);
    QString getApplicationId();
    void setApplicationId(QString application_id);
    QString getParentId();
    void  setParentId(QString parent_id);
    QString getLastPinTimestamp();
    void setLastPinTimestamp(QString last_pin_timestamp);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(Channel)

#endif // CHANNEL_H
