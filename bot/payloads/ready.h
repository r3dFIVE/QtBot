#ifndef READY_H
#define READY_H

#include "channel.h"
#include "guild.h"
#include "jsonserializable.h"
#include "user.h"

#include <QObject>

class Ready : public JsonSerializable
{
    Q_OBJECT

public:
    const QString V = "v";
    const QString USER = "user";
    const QString PRIVATE_CHANNELS = "private_channels";
    const QString GUILDS = "guilds";
    const QString SESSION_ID = "session_id";
    const QString SHARD = "shard";

    Q_PROPERTY(int v READ getV WRITE setV)
    int v;

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    User user;

    Q_PROPERTY(QJsonArray private_channels READ getPrivateChannels WRITE setPrivateChannels)
    QList<Channel> private_channels;

    Q_PROPERTY(QJsonArray guilds READ getGuilds WRITE setGuilds)
    QList<Guild> guilds;

    Q_PROPERTY(QString session_id READ getSessionId WRITE setSessionId)
    QString session_id;

    Q_PROPERTY(QJsonArray shard READ getShard WRITE setShard)
    QSharedPointer<int> shard[2];

    int getV();
    void setV(int v);
    QJsonObject getUser();
    void setUser(QJsonObject user);
    QJsonArray getPrivateChannels();
    void setPrivateChannels(QJsonArray private_channels);
    QJsonArray getGuilds();
    void setGuilds(QJsonArray guilds);
    QString getSessionId();
    void setSessionId(QString session_id);
    QJsonArray getShard();
    void setShard(QJsonArray shard);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(Ready)

#endif // READY_H
