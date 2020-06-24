#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "identifyproperties.h"
#include "jsonserializable.h"
#include "updatestatus.h"

#include <QSharedPointer>
#include <QJsonArray>

class UpdateStatus;

class Identify : public JsonSerializable
{

    Q_OBJECT
public:
    const QString TOKEN = "token";
    const QString PROPERTIES = "properties";
    const QString COMPRESS = "compress";
    const QString LARGE_THRESHOLD = "large_threshold";
    const QString SHARD = "shard";
    const QString PRESENCE = "presence";
    const QString GUILD_SUBSCRIPTIONS = "guild_subscriptions";
    const QString INTENTS = "intents";

    Q_PROPERTY(QString token READ getToken WRITE setToken)
    QString token;

    Q_PROPERTY(QJsonObject properties READ getProperties WRITE setProperties)
    QSharedPointer<IdentifyProperties> properties = QSharedPointer<IdentifyProperties>(new IdentifyProperties);

    Q_PROPERTY(QJsonValue compress READ getCompress WRITE setCompress)
    QSharedPointer<bool> compress;

    Q_PROPERTY(QJsonValue large_threshold READ getLargeThreshold WRITE setLargeThreshold)
    QSharedPointer<int> large_threshold;

    Q_PROPERTY(QJsonArray shard READ getShard WRITE setShard)
    QSharedPointer<int> shard[2];

    Q_PROPERTY(QJsonObject presence READ getPresence WRITE setPresence)
    QSharedPointer<UpdateStatus> presence;

    Q_PROPERTY(QJsonValue guild_subscriptions READ getGuildSubscriptions WRITE setGuildSubscriptions)
    QSharedPointer<bool> guild_subscriptions;

    Q_PROPERTY(QJsonValue intents READ getIntents WRITE setIntents)
    QSharedPointer<int> intents;

    QString getToken();
    void setToken (QString token);
    QJsonObject getProperties();
    void setProperties(QJsonObject properties);
    QJsonValue getCompress();
    void setCompress(QJsonValue compress);
    QJsonValue getLargeThreshold();
    void setLargeThreshold(QJsonValue large_threshold);
    QJsonArray getShard();
    void setShard(QJsonArray shard);
    QJsonObject getPresence();
    void setPresence(QJsonObject presence);
    QJsonValue getGuildSubscriptions();
    void setGuildSubscriptions(QJsonValue guild_subscriptions);
    QJsonValue getIntents();
    void setIntents(QJsonValue intents);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(Identify)

#endif // IDENTIFY_H
