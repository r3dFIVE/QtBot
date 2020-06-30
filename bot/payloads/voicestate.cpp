#include "voicestate.h"

#include "util/jsonutils.h"

QString
VoiceState::getGuildId() {
    return guild_id;
}

void
VoiceState::setGuildId(QString guild_id) {
    this->guild_id = guild_id;
}

QString
VoiceState::getChannelId() {
    return channel_id;
}

void
VoiceState::setChannelId(QString channel_id) {
    this->channel_id = channel_id;
}

QString
VoiceState::getUserId() {
    return user_id;
}

void
VoiceState::setUserId(QString user_id) {
    this->user_id = user_id;
}

QJsonObject
VoiceState::getMember() {
    if (member) {
        return member->toQJsonObject();
    } else {
        return QJsonObject();
    }
}

void
VoiceState::setMember(QJsonObject member) {
    if (!member.isEmpty()) {
        this->member = QSharedPointer<GuildMember>(new GuildMember);
        JsonUtils::readFromJson(*this->member, member);
    }
}

QString
VoiceState::getSessionId() {
    return session_id;
}

void
VoiceState::setSessionId(QString session_id) {
    this->session_id = session_id;
}

bool
VoiceState::getDeaf() {
    return deaf;
}

void
VoiceState::setDeaf(bool deaf) {
    this->deaf = deaf;
}

bool
VoiceState::getMute() {
    return mute;
}

void
VoiceState::setMute(bool mute) {
    this->mute = mute;
}

bool
VoiceState::getSelfDeaf() {
    return self_deaf;
}

void
VoiceState::setSelfDeaf(bool self_deaf) {
    this->self_deaf = self_deaf;
}

bool
VoiceState::getSelfMute() {
    return self_mute;
}

void
VoiceState::setSelfMute(bool self_mute) {
    this->self_mute = self_mute;
}

QJsonValue
VoiceState::getSelfStream() {
    if (self_stream) {
        return *self_stream;
    } else {
        return QJsonValue();
    }
}

void
VoiceState::setSelfStream(QJsonValue self_stream) {
    if (!self_stream.isNull()) {
        this->self_stream = QSharedPointer<bool>(new bool(self_stream.toBool()));
    }
}

bool
VoiceState::getSuppress() {
    return suppress;
}

void
VoiceState::setSuppress(bool suppress) {
    this->suppress = suppress;
}

void
VoiceState::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
VoiceState::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
