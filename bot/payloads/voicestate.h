/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

    VoiceState(QObject *parent = nullptr) : JsonSerializable(parent) {}
    VoiceState(const VoiceState &other, QObject *parent = nullptr) : JsonSerializable(other, parent) {}
    VoiceState(const QByteArray &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    VoiceState(const QJsonObject &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}
    VoiceState(const QString &json, QObject *parent = nullptr) : JsonSerializable(json, parent) {}

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
