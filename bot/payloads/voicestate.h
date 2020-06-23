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

    QString
    getGuildId() {
        return guild_id;
    }

    void
    setGuildId(QString guild_id) {
        this->guild_id = guild_id;
    }

    QString
    getChannelId() {
        return channel_id;
    }

    void
    setChannelId(QString channel_id) {
        this->channel_id = channel_id;
    }

    QString
    getUserId() {
        return user_id;
    }

    void
    setUserId(QString user_id) {
        this->user_id = user_id;
    }

    QJsonObject
    getMember() {
        if (member) {
            return member->toQJsonObject();
        } else {
            return QJsonObject();
        }
    }

    void
    setMember(QJsonObject member) {
        if (!member.isEmpty()) {
            this->member = QSharedPointer<GuildMember>(new GuildMember);
            JsonUtils::readFromJson(*this->member, member);
        }
    }

    QString
    getSessionId() {
        return session_id;
    }

    void
    setSessionId(QString session_id) {
        this->session_id = session_id;
    }

    bool
    getDeaf() {
        return deaf;
    }

    void
    setDeaf(bool deaf) {
        this->deaf = deaf;
    }

    bool
    getMute() {
        return mute;
    }

    void
    setMute(bool mute) {
        this->mute = mute;
    }

    bool
    getSelfDeaf() {
        return self_deaf;
    }

    void
    setSelfDeaf(bool self_deaf) {
        this->self_deaf = self_deaf;
    }

    bool
    getSelfMute() {
        return self_mute;
    }

    void
    setSelfMute(bool self_mute) {
        this->self_mute = self_mute;
    }

    QJsonValue
    getSelfStream() {
        if (self_stream) {
            return *self_stream;
        } else {
            return QJsonValue();
        }
    }

    void
    setSelfStream(QJsonValue self_stream) {
        if (!self_stream.isNull()) {
            this->self_stream = QSharedPointer<bool>(new bool(self_stream.toBool()));
        }
    }

    bool
    getSuppress() {
        return suppress;
    }

    void
    setSuppress(bool suppress) {
        this->suppress = suppress;
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(VoiceState)

#endif // VOICESTATE_H
