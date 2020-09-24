#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

#include "payloads/jsonserializable.h"


class EventContext : public JsonSerializable
{
    Q_OBJECT

    void buildContext(const QJsonObject &json);

public:

    static const QString EMOJI;
    static const QString EVENT_NAME;
    static const QString CHANNEL_ID;
    static const QString GUILD_ID;
    static const QString INTEGRATION_ID;
    static const QString ROLE_ID;
    static const QString MESSAGE_ID;
    static const QString OVERWRITE_ID;
    static const QString WEBHOOK_ID;
    static const QString USER_ID;
    static const QString CONTENT;
    static const QString AUTHOR;
    static const QString SOURCE_PAYLOAD;
    static const QString TARGET_PAYLOAD;

    EventContext() {}
    EventContext(const QByteArray &json);
    EventContext(const QJsonObject &json);
    EventContext(const EventContext &other) {
        _jsonObject = other._jsonObject;
    }
    ~EventContext() {}

    EventContext &operator=(const EventContext &other) {
        _jsonObject = other._jsonObject;

        return *this;
    }

    Q_PROPERTY(QJsonValue emoji READ getEmoji WRITE setEmoji)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue message_id READ getMessageId WRITE setMessageId)
    Q_PROPERTY(QJsonValue overwrite_id READ getOverwriteId WRITE setOverwriteId)
    Q_PROPERTY(QJsonValue webhook_id READ getWebhookId WRITE setWebhookId)
    Q_PROPERTY(QJsonValue user_id READ getUserId WRITE setUserId)
    Q_PROPERTY(QJsonValue role_id READ getRoleId WRITE setRoleId)
    Q_PROPERTY(QJsonValue content READ getContent WRITE setContent)
    Q_PROPERTY(QJsonValue event_name READ getEventName WRITE setEventName)
    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QJsonObject source_payload READ getSourcePayload WRITE setSourcePayload)
    Q_PROPERTY(QJsonObject target_payload READ getTargetPayload WRITE setTargetPayload)

    inline void removePropertyFromTarget(const QString &key) {
        _jsonObject[TARGET_PAYLOAD].toObject().remove(key);
    }

    inline void addPropertyToTarget(const QString &key, const QJsonValue &value) {
        _jsonObject[TARGET_PAYLOAD].toObject()[key] = value;
    }

public slots:
    QJsonObject getAuthor() const;
    QJsonObject getSourcePayload() const;
    QJsonObject getTargetPayload() const;
    QJsonValue getChannelId() const;
    QJsonValue getContent() const;
    QJsonValue getEmoji() const;
    QJsonValue getEventName() const;
    QJsonValue getMessageId() const;
    QJsonValue getOverwriteId() const;
    QJsonValue getGuildId() const;
    QJsonValue getRoleId() const;
    QJsonValue getUserId() const;
    QJsonValue getWebhookId() const;
    QJsonValue getIntegrationId() const;
    void setAuthor(const QJsonObject &author);
    void setChannelId(const QJsonValue &channelId);
    void setContent(const QJsonValue &content);
    void setEmoji(const QJsonValue &emoji);
    void setEventName(const QJsonValue &eventName);
    void setGuildId(const QJsonValue &guildId);
    void setRoleId(const QJsonValue &roleId);
    void setMessageId(const QJsonValue &messageId);
    void setOverwriteId(const QJsonValue &overwriteId);
    void setSourcePayload(const QJsonObject &sourcePayload);
    void setTargetPayload(const QJsonObject &targetPayload);
    void setUserId(const QJsonValue &userId);
    void setIntegrationId(const QJsonValue &webhookId);
    void setWebhookId(const QJsonValue &webhookId);
};

Q_DECLARE_METATYPE(EventContext)

#endif // EVENTCONTEXT_H
