#ifndef VOICESTATE_H
#define VOICESTATE_H

#include "guildmember.h"
#include "jsonserializable.h"


class VoiceState : public JsonSerializable
{
    Q_OBJECT

public:

    const QString GUILD_ID = "guild_id";
    const QString CHANNEL_ID = "channel_id";
    const QString USER_ID = "user_id";
    const QString MEMBER = "memeber";
    const QString SESSION_ID = "session_id";
    const QString DEAF = "deaf";
    const QString MUTE = "mute";
    const QString SELF_DEAF = "self_deaf";
    const QString SELF_MUTE = "self_mute";
    const QString SELF_STREAM = "self_stream";
    const QString SUPPRESS = "suppress";

    Q_PROPERTY(QString guild_id READ getGuildId WRITE setGuildId)
    QString guild_id;

    Q_PROPERTY(QString channel_id READ getChannelId WRITE setChannelId)
    QString channel_id;

    Q_PROPERTY(QString user_id READ getUserId WRITE setUserId)
    QString user_id;

    Q_PROPERTY(QJsonObject member READ getMember WRITE setMember)
    QSharedPointer<GuildMember> member;

    Q_PROPERTY(QString session_id READ getSessionId WRITE setSessionId)
    QString session_id;

    Q_PROPERTY(bool deaf READ getDeaf WRITE setDeaf)
    bool deaf;

    Q_PROPERTY(bool mute READ getMute WRITE setMute)
    bool mute;

    Q_PROPERTY(bool self_deaf READ getSelfDeaf WRITE setSelfDeaf)
    bool self_deaf;

    Q_PROPERTY(bool self_mute READ getSelfMute WRITE setSelfMute)
    bool self_mute;

    Q_PROPERTY(QJsonValue self_stream READ getSelfStream WRITE setSelfStream)
    QSharedPointer<bool> self_stream;

    Q_PROPERTY(bool suppress READ getSuppress WRITE setSuppress)
    bool suppress;

    QString getGuildId();
    void setGuildId(QString guild_id);
    QString getChannelId();
    void setChannelId(QString channel_id);
    QString getUserId();
    void setUserId(QString user_id);
    QJsonObject getMember();
    void setMember(QJsonObject member);
    QString getSessionId();
    void setSessionId(QString session_id);
    bool getDeaf();
    void setDeaf(bool deaf);
    bool getMute();
    void setMute(bool mute);
    bool getSelfDeaf();
    void setSelfDeaf(bool self_deaf);
    bool getSelfMute();
    void setSelfMute(bool self_mute);
    QJsonValue getSelfStream();
    void setSelfStream(QJsonValue self_stream);
    bool getSuppress();
    void setSuppress(bool suppress);
    void read(const QJsonObject &jsonObject) override;
    void write(QJsonObject &jsonObject) override;
};

Q_DECLARE_METATYPE(VoiceState)

#endif // VOICESTATE_H
