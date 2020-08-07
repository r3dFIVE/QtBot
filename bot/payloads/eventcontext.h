#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

#include "payloads/jsonserializable.h"


class EventContext : public JsonSerializable
{
    Q_OBJECT

    void buildContext(const QJsonObject &json);

public:

    static const QString CHANNEL_ID;
    static const QString GUILD_ID;
    static const QString CONTENT;
    static const QString AUTHOR;
    static const QString COMMAND;
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

    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue content READ getContent WRITE setContent)
    Q_PROPERTY(QJsonValue command READ getCommand WRITE setCommand)
    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QJsonObject source_payload READ getSourcePayload WRITE setSourcePayload)
    Q_PROPERTY(QJsonObject target_payload READ getTargetPayload WRITE setTargetPayload)

public slots:
    QJsonObject getAuthor() const;
    QJsonObject getSourcePayload() const;
    QJsonObject getTargetPayload() const;
    QJsonValue getChannelId() const;
    QJsonValue getCommand() const;
    QJsonValue getContent() const;
    QJsonValue getGuildId() const;
    void setAuthor(const QJsonObject &author);
    void setChannelId(const QJsonValue &channelId);
    void setCommand(const QJsonValue &command);
    void setContent(const QJsonValue &content);
    void setGuildId(const QJsonValue &guildId);
    void setSourcePayload(const QJsonObject &sourcePayload);
    void setTargetPayload(const QJsonObject &targetPayload);
};

Q_DECLARE_METATYPE(EventContext)

#endif // EVENTCONTEXT_H
