/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "message.h"


const QString Message::ID = "id";
const QString Message::CHANNEL_ID = "channel_id";
const QString Message::GUILD_ID = "guild_id";
const QString Message::AUTHOR = "author";
const QString Message::MEMBER = "member";
const QString Message::CONTENT = "content";
const QString Message::TIMESTAMP = "timestamp";
const QString Message::EDITED_TIMESTAMP = "edited_timestamp";
const QString Message::TTS = "tts";
const QString Message::MENTION_EVERYONE = "mention_everyone";
const QString Message::MENTIONS = "mentions";
const QString Message::MENTION_ROLES = "mention_roles";
const QString Message::MENTION_CHANNELS = "mention_channels";
const QString Message::ATTACHMENTS = "attachments";
const QString Message::EMBEDS = "embeds";
const QString Message::REACTIONS = "reactions";
const QString Message::NONCE = "nonce";
const QString Message::PINNED = "pinned";
const QString Message::WEBHOOK_ID = "webhook_id";
const QString Message::TYPE = "type";
const QString Message::ACTIVITY = "activity";
const QString Message::APPLICATION = "application";
const QString Message::MESSAGE_REFERENCE = "message_reference";
const QString Message::FLAGS = "flags";

QJsonValue
Message::getId() const {
    return _jsonObject[ID];
}

void
Message::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
Message::getChannelId() const {
    return _jsonObject[CHANNEL_ID];
}

void
Message::setChannelId(const QJsonValue &channel_id) {
    _jsonObject[CHANNEL_ID] = channel_id;
}

QJsonValue
Message::getGuildId() const {
    return _jsonObject[GUILD_ID];
}

void
Message::setGuildId(const QJsonValue &guildId) {
    _jsonObject[GUILD_ID] = guildId;
}

QJsonObject
Message::getAuthor() const {
    return _jsonObject[AUTHOR].toObject();
}

void
Message::setAuthor(const QJsonObject &author) {
    _jsonObject[AUTHOR] = author;
}

QJsonObject
Message::getMember() const {
    return _jsonObject[MEMBER].toObject();
}

void
Message::setMember(const QJsonObject &member) {
    _jsonObject[MEMBER] = member;
}

QJsonValue
Message::getContent() const {
    return _jsonObject[CONTENT];
}

void
Message::setContent(const QJsonValue &content) {
    _jsonObject[CONTENT] = content;
}

QJsonValue
Message::getTimestamp() const {
    return _jsonObject[TIMESTAMP];
}

void
Message::setTimestamp(const QJsonValue &timestamp) {
    _jsonObject[TIMESTAMP] = timestamp;
}

QJsonValue
Message::getEditedTimestamp() const {
    return _jsonObject[EDITED_TIMESTAMP];
}

void
Message::setEditedTimestamp(const QJsonValue &edited_timestamp) {
    _jsonObject[EDITED_TIMESTAMP] = edited_timestamp;
}

QJsonValue
Message::getTTS() const {
    return _jsonObject[TTS];
}

void
Message::setTTS(const QJsonValue &tts) {
    _jsonObject[TTS] = tts;
}

QJsonValue
Message::getMentionEveryone() const {
    return _jsonObject[MENTION_EVERYONE];
}

void
Message::setMentionEveryone(const QJsonValue &mentionEveryone) {
    _jsonObject[MENTION_EVERYONE] = mentionEveryone;
}

QJsonArray
Message::getMentions() const {
    return _jsonObject[MENTIONS].toArray();
}

void
Message::setMentions(const QJsonArray &mentions) {
    _jsonObject[MENTIONS] = mentions;
}

QJsonArray
Message::getMentionRoles() const {
    return _jsonObject[MENTION_ROLES].toArray();
}

void
Message::setMentionRoles(const QJsonArray &mentionRoles) {
    _jsonObject[MENTION_ROLES] = mentionRoles;
}

QJsonArray
Message::getMentionChannels() const {
    return _jsonObject[MENTION_CHANNELS].toArray();
}

void
Message::setMentionChannels(const QJsonArray &mentionChannels) {
    _jsonObject[MENTION_CHANNELS] = mentionChannels;
}

QJsonArray
Message::getAttachments() const {
    return _jsonObject[ATTACHMENTS].toArray();
}

void
Message::setAttachments(const QJsonArray &attachments) {
    _jsonObject[ATTACHMENTS] = attachments;
}

QJsonArray
Message::getEmbeds() const {
    return _jsonObject[EMBEDS].toArray();
}

void
Message::setEmbeds(const QJsonArray &embeds) {
    _jsonObject[EMBEDS] = embeds;
}

QJsonArray
Message::getReactions() const {
    return _jsonObject[REACTIONS].toArray();
}

void
Message::setReactions(const QJsonArray &ractions) {
    _jsonObject[REACTIONS] = ractions;
}

QJsonValue
Message::getNonce() const {
    return _jsonObject[NONCE];
}

void
Message::setNonce(const QJsonValue &nonce) {
    _jsonObject[NONCE] = nonce;
}

QJsonValue
Message::getPinned() const {
    return _jsonObject[PINNED];
}

void
Message::setPinned(const QJsonValue &pinned) {
    _jsonObject[PINNED] = pinned;
}

QJsonValue
Message::getWebhookId() const {
    return _jsonObject[WEBHOOK_ID];
}

void
Message::setWebhookId(const QJsonValue &webhookId) {
    _jsonObject[WEBHOOK_ID] = webhookId;
}

QJsonValue
Message::getType() const {
    return _jsonObject[TYPE];
}

void
Message::setType(const QJsonValue &type) {
    _jsonObject[TYPE] = type;
}

QJsonObject
Message::getActivity() const {
    return _jsonObject[ACTIVITY].toObject();
}

void
Message::setActivity(const QJsonObject &activity) {
    _jsonObject[ACTIVITY] = activity;
}

QJsonObject
Message::getApplication() const {
    return _jsonObject[APPLICATION].toObject();
}

void
Message::setApplication(const QJsonObject &application) {
    _jsonObject[APPLICATION] = application;
}

QJsonObject
Message::getMessageReference() const {
    return _jsonObject[MESSAGE_REFERENCE].toObject();
}

void
Message::setMessageReference(const QJsonObject &messageReference) {
    _jsonObject[MESSAGE_REFERENCE] = messageReference;
}

QJsonValue
Message::getFlags() const {
    return _jsonObject[FLAGS];
}

void
Message::setFlags(const QJsonValue &flags) {
    _jsonObject[FLAGS] = flags;
}
