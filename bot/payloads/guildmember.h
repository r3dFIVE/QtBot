#ifndef GUILDMEMBER_H
#define GUILDMEMBER_H

#include "jsonserializable.h"
#include "user.h"


class GuildMember : public JsonSerializable
{
    Q_OBJECT

public:
    const QString USER = "user";
    const QString NICK = "nick";
    const QString ROLES = "roles";
    const QString JOINED_AT = "joined_at";
    const QString PREMIUM_SINCE = "premium_since";
    const QString DEAF = "deaf";
    const QString MUTE = "mute";

    Q_PROPERTY(QJsonObject user READ getUser WRITE setUser)
    QSharedPointer<User> user;

    Q_PROPERTY(QString nick READ getNick WRITE setNick)
    QString nick;

    Q_PROPERTY(QJsonArray roles READ getRoles WRITE setRoles)
    QList<QString> roles;

    Q_PROPERTY(QString joined_at READ getJoinedAt WRITE setJoinedAt)
    QString joined_at;

    Q_PROPERTY(QString premium_since READ getPremiumSince WRITE setPremiumSince)
    QString premium_since;

    Q_PROPERTY(bool deaf READ getDeaf WRITE setDeaf)
    bool deaf;

    Q_PROPERTY(bool mute READ getMute WRITE setDeaf)
    bool mute;

    QJsonObject getUser();
    void setUser(QJsonObject user);
    QString getNick();
    void setNick(QString nick);
    QJsonArray getRoles();
    void setRoles(QJsonArray roles);
    QString getJoinedAt();
    void setJoinedAt(QString joined_at);
    QString getPremiumSince();
    void setPremiumSince(QString premium_since);
    bool getDeaf();
    void setDeaf(bool deaf);
    bool getMute();
    void setMute(bool mute);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(GuildMember)

#endif // GUILDMEMBER_H
