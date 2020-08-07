#ifndef READY_H
#define READY_H

#include "jsonserializable.h"


class Ready : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString V;
    static const QString USER;
    static const QString PRIVATE_CHANNELS;
    static const QString GUILDS;
    static const QString SESSION_ID;
    static const QString SHARD;

    Ready() {}
    Ready(const QByteArray &json) : JsonSerializable(json) {}
    Ready(const QJsonObject &json) : JsonSerializable(json) {}
    Ready(const QString &json) : JsonSerializable(json) {}

    QJsonArray getShard() const;
    QJsonArray getGuilds() const;
    QJsonArray getPrivateChannels() const;
    QJsonObject getUser() const;
    QJsonValue getSessionId() const;
    QJsonValue getV() const;
    void setGuilds(const QJsonArray &guilds);
    void setPrivateChannels(const QJsonArray &privateChannels);
    void setSessionId(const QJsonValue &sessionId);
    void setShard(const QJsonArray &shard);
    void setUser(const QJsonObject &user);
    void setV(const QJsonValue &v);

    Q_PROPERTY(QJsonValue v READ getV WRITE setV)
    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    Q_PROPERTY(QJsonArray private_channels READ getPrivateChannels WRITE setPrivateChannels)
    Q_PROPERTY(QJsonArray guilds READ getGuilds WRITE setGuilds)
    Q_PROPERTY(QJsonValue session_id READ getSessionId WRITE setSessionId)
    Q_PROPERTY(QJsonArray shard READ getShard WRITE setShard)
};

Q_DECLARE_METATYPE(Ready)

#endif // READY_H
