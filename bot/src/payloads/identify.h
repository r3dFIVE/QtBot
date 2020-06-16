#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "properties.h"
#include "jsonserializeable.h"
#include "updatestatus.h"

#include <QSharedPointer>

class Identify : public JsonSerializeable
{
    const QString TOKEN = "token";
    const QString PROPERTIES = "properties";
    const QString COMPRESS = "compress";
    const QString LARGE_THRESHOLD = "large_threshold";
    const QString SHARD = "shard";
    const QString PRESENCE = "presence";
    const QString GUILD_SUBSCRIPTIONS = "guild_subscriptions";
    const QString INTENTS = "intents";

public:
    QString token;
    Properties properties;
    QSharedPointer<bool> compress;
    QSharedPointer<int> large_threshold;
    QSharedPointer<int> shard[2];
    QSharedPointer<UpdateStatus> presence;
    QSharedPointer<bool> guild_subscriptions;
    QSharedPointer<int> intents;

    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) const override;
};

#endif // IDENTIFY_H
