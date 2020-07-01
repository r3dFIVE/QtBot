#ifndef MESSAGEREFERENCE_H
#define MESSAGEREFERENCE_H

#include "jsonserializable.h"

#include <QObject>

class MessageReference : public JsonSerializable
{
    Q_OBJECT

public:

    Q_PROPERTY(QJsonValue message_id READ getMessageId WRITE setMessageId)
    QJsonValue message_id;

    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    QJsonValue channel_id;

    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    QJsonValue guild_id;

    QJsonValue getMessageId() const;
    void setMessageId(const QJsonValue &value);
    QJsonValue getChannelId() const;
    void setChannelId(const QJsonValue &value);
    QJsonValue getGuildId() const;
    void setGuildId(const QJsonValue &value);

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;

    MessageReference() {}
    ~MessageReference() {}
};

Q_DECLARE_METATYPE(MessageReference)


#endif // MESSAGEREFERENCE_H
