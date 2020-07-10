#ifndef EVENTCONTEXT_H
#define EVENTCONTEXT_H

#include <QObject>
#include <QJsonValue>
#include <QJsonObject>


class EventContext : public QObject
{
    Q_OBJECT

    const static QString CHANNEL_ID;
    const static QString GUILD_ID;
    const static QString CONTENT;
    const static QString AUTHOR;

public:

    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    QJsonValue channel_id;

    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    QJsonValue guild_id;

    Q_PROPERTY(QJsonValue content_id READ getContent WRITE setContent)
    QJsonValue content;

    Q_PROPERTY(QJsonObject author READ getAuthor WRITE setAuthor)
    QJsonObject author;

    Q_PROPERTY(QJsonObject source_payload READ getSourcePayload WRITE setSourcePayload)
    QJsonObject source_payload;

    Q_PROPERTY(QJsonObject target_payload READ getTargetPayload WRITE setTargetPayload)
    QJsonObject target_payload;


    EventContext() {}
    EventContext(const QJsonObject &payload);
    EventContext(const EventContext &other) { Q_UNUSED(other) }
    ~EventContext() {}

    QJsonValue getChannelId() const;
    void setChannelId(const QJsonValue &value);
    QJsonValue getGuildId() const;
    void setGuildId(const QJsonValue &value);
    QJsonValue getContent() const;
    void setContent(const QJsonValue &value);
    QJsonObject getAuthor() const;
    void setAuthor(const QJsonObject &value);
    QJsonObject getSourcePayload() const;
    void setSourcePayload(const QJsonObject &value);
    QJsonObject getTargetPayload() const;
    void setTargetPayload(const QJsonObject &value);

signals:

};

Q_DECLARE_METATYPE(EventContext)

#endif // EVENTCONTEXT_H
