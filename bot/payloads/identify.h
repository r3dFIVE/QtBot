#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "jsonserializable.h"


class Identify : public JsonSerializable
{

    Q_OBJECT
public:
    static const QString TOKEN;
    static const QString PROPERTIES;
    static const QString COMPRESS;
    static const QString LARGE_THRESHOLD;
    static const QString SHARD;
    static const QString PRESENCE;
    static const QString GUILD_SUBSCRIPTIONS;
    static const QString INTENTS;

    Identify() {}
    Identify(const QByteArray &json) : JsonSerializable(json) {}
    Identify(const QJsonObject &json) : JsonSerializable(json) {}
    Identify(const QString &json) : JsonSerializable(json) {}

    QJsonArray getShard() const;
    QJsonObject getPresence() const;
    QJsonObject getProperties() const;
    QJsonValue getCompress() const;
    QJsonValue getGuildSubscriptions() const;
    QJsonValue getIntents() const;
    QJsonValue getLargeThreshold() const;
    QJsonValue getToken() const;
    void setCompress(const QJsonValue &getCompress);
    void setGuildSubscriptions(const QJsonValue &getGuildSubscriptions);
    void setIntents(const QJsonValue &getIntents);
    void setLargeThreshold(const QJsonValue &getLargeThreshold);
    void setPresence(const QJsonObject &getPresence);
    void setProperties(const QJsonObject &getProperties);
    void setShard(const QJsonArray &getShard);
    void setToken (const QJsonValue &getToken);

    Q_PROPERTY(QJsonValue getToken READ getToken WRITE setToken)
    Q_PROPERTY(QJsonObject getProperties READ getProperties WRITE setProperties)
    Q_PROPERTY(QJsonValue getCompress READ getCompress WRITE setCompress)
    Q_PROPERTY(QJsonValue large_threshold READ getLargeThreshold WRITE setLargeThreshold)
    Q_PROPERTY(QJsonArray getShard READ getShard WRITE setShard)
    Q_PROPERTY(QJsonObject getPresence READ getPresence WRITE setPresence)
    Q_PROPERTY(QJsonValue guild_subscriptions READ getGuildSubscriptions WRITE setGuildSubscriptions)
    Q_PROPERTY(QJsonValue getIntents READ getIntents WRITE setIntents)
};

Q_DECLARE_METATYPE(Identify)

#endif // IDENTIFY_H
