#ifndef VOICESTATE_H
#define VOICESTATE_H

#include "jsonserializable.h"


class VoiceState : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString GUILD_ID;
    static const QString CHANNEL_ID;
    static const QString USER_ID;
    static const QString MEMBER;
    static const QString SESSION_ID;;
    static const QString DEAF;
    static const QString MUTE;
    static const QString SELF_DEAF;
    static const QString SELF_MUTE;
    static const QString SELF_STREAM;
    static const QString SUPPRESS;

    VoiceState() {}
    VoiceState(const QByteArray &json) : JsonSerializable(json) {}
    VoiceState(const QJsonObject &json) : JsonSerializable(json) {}
    VoiceState(const QString &json) : JsonSerializable(json) {}

    QJsonObject getMember() const;
    QJsonValue getChannelId() const;
    QJsonValue getDeaf() const;
    QJsonValue getGuildId() const;
    QJsonValue getMute() const;
    QJsonValue getSelfDeaf() const;
    QJsonValue getSelfMute() const;
    QJsonValue getSelfStream() const;
    QJsonValue getSessionId() const;
    QJsonValue getSuppress() const;
    QJsonValue getUserId() const;
    void setChannelId(const QJsonValue &channelId);
    void setDeaf(const QJsonValue &deaf);
    void setGuildId(const QJsonValue &guildId);
    void setMember(const QJsonObject &member);
    void setMute(const QJsonValue &mute);
    void setSelfDeaf(const QJsonValue &selfDeaf);
    void setSelfMute(const QJsonValue &selfMute);
    void setSelfStream(const QJsonValue &selfStream);
    void setSessionId(const QJsonValue &sessionId);
    void setSuppress(const QJsonValue &suppress);
    void setUserId(const QJsonValue &userId);

    Q_PROPERTY(QJsonValue guild_id READ getGuildId WRITE setGuildId)
    Q_PROPERTY(QJsonValue channel_id READ getChannelId WRITE setChannelId)
    Q_PROPERTY(QJsonValue user_id READ getUserId WRITE setUserId)
    Q_PROPERTY(QJsonObject member READ getMember WRITE setMember)
    Q_PROPERTY(QJsonValue session_id READ getSessionId WRITE setSessionId)
    Q_PROPERTY(QJsonValue deaf READ getDeaf WRITE setDeaf)
    Q_PROPERTY(QJsonValue mute READ getMute WRITE setMute)
    Q_PROPERTY(QJsonValue self_deaf READ getSelfDeaf WRITE setSelfDeaf)
    Q_PROPERTY(QJsonValue self_mute READ getSelfMute WRITE setSelfMute)
    Q_PROPERTY(QJsonValue self_stream READ getSelfStream WRITE setSelfStream)
    Q_PROPERTY(QJsonValue suppress READ getSuppress WRITE setSuppress)
};

Q_DECLARE_METATYPE(VoiceState)

#endif // VOICESTATE_H
