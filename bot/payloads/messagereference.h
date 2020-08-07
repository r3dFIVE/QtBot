#ifndef MESSAGEREFERENCE_H
#define MESSAGEREFERENCE_H

#include "jsonserializable.h"


class MessageReference : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString CHANNEL_ID;
    static const QString GUILD_ID;
    static const QString MESSAGE_ID;

    MessageReference() {}
    MessageReference(const QByteArray &json) : JsonSerializable(json) {}
    MessageReference(const QJsonObject &json) : JsonSerializable(json) {}
    MessageReference(const QString &json) : JsonSerializable(json) {}

    QJsonValue getChannelId() const;
    QJsonValue getGuildId() const;
    QJsonValue getMessageId() const;
    void setChannelId(const QJsonValue &channelId);
    void setGuildId(const QJsonValue &guildId);
    void setMessageId(const QJsonValue &messageId);

    Q_PROPERTY(QJsonValue message_id READ getMessageId WRITE setMessageId)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
};

Q_DECLARE_METATYPE(MessageReference)


#endif // MESSAGEREFERENCE_H
