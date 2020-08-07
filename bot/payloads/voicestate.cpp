#include "voicestate.h"


const QString VoiceState::GUILD_ID = "guild_id";
const QString VoiceState::CHANNEL_ID = "channel_id";
const QString VoiceState::USER_ID = "user_id";
const QString VoiceState::MEMBER = "member";
const QString VoiceState::SESSION_ID = "session_id";
const QString VoiceState::DEAF = "deaf";
const QString VoiceState::MUTE = "mute";
const QString VoiceState::SELF_DEAF = "self_deaf";
const QString VoiceState::SELF_MUTE = "self_mute";
const QString VoiceState::SELF_STREAM = "self_stream";
const QString VoiceState::SUPPRESS = "suppress";

QJsonValue
VoiceState::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
VoiceState::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonValue
VoiceState::getChannelId() const {
    return _jsonObject[CHANNEL_ID];
}

void
VoiceState::setChannelId(const QJsonValue &channelId) {
    _jsonObject[CHANNEL_ID] = channelId;
}

QJsonValue
VoiceState::getUserId() const {
    return _jsonObject[USER_ID];
}

void
VoiceState::setUserId(const QJsonValue &userId) {
    _jsonObject[USER_ID] = userId;
}

QJsonObject
VoiceState::getMember() const {
    return _jsonObject[MEMBER].toObject();
}

void
VoiceState::setMember(const QJsonObject &member) {
    _jsonObject[MEMBER] = member;
}

QJsonValue
VoiceState::getSessionId() const {
    return _jsonObject[SESSION_ID];
}

void
VoiceState::setSessionId(const QJsonValue &sessionId) {
    _jsonObject[SESSION_ID] = sessionId;
}

QJsonValue
VoiceState::getDeaf() const {
    return _jsonObject[DEAF];
}

void
VoiceState::setDeaf(const QJsonValue &deaf) {
    _jsonObject[DEAF] = deaf;
}

QJsonValue
VoiceState::getMute() const {
    return _jsonObject[MUTE];
}

void
VoiceState::setMute(const QJsonValue &mute) {
    _jsonObject[MUTE] = mute;
}

QJsonValue
VoiceState::getSelfDeaf() const {
    return _jsonObject[SELF_DEAF];
}

void
VoiceState::setSelfDeaf(const QJsonValue &selfDeaf) {
    _jsonObject[SELF_DEAF] = selfDeaf;
}

QJsonValue
VoiceState::getSelfMute() const {
    return _jsonObject[SELF_MUTE];
}

void
VoiceState::setSelfMute(const QJsonValue &selfMute) {
    _jsonObject[SELF_MUTE] = selfMute;
}

QJsonValue
VoiceState::getSelfStream() const {
    return _jsonObject[SELF_STREAM];
}

void
VoiceState::setSelfStream(const QJsonValue &selfStream) {
    _jsonObject[SELF_STREAM] = selfStream;
}

QJsonValue
VoiceState::getSuppress() const {
    return _jsonObject[SUPPRESS];
}

void
VoiceState::setSuppress(const QJsonValue &suppress) {
    _jsonObject[SUPPRESS] = suppress;
}
