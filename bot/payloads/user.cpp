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

#include "user.h"


const QString User::ID = "id";
const QString User::USERNAME = "username";
const QString User::DISCRIMINATOR = "discriminator";
const QString User::AVATAR = "avatar";
const QString User::BOT = "bot";
const QString User::SYSTEM = "system";
const QString User::MFA_ENABLED = "mfa_enabled";
const QString User::LOCALE = "locale";
const QString User::VERIFIED = "verified";
const QString User::EMAIL = "email";
const QString User::FLAGS = "flags";
const QString User::PREMIUM_TYPE = "premium_type";
const QString User::PUBLIC_FLAGS = "public_flags";

QJsonValue
User::getId() const {
    return _jsonObject[ID];
}

void
User::setId(const QJsonValue &id) {
    _jsonObject[ID] = id;
}

QJsonValue
User::getUsername() const {
    return _jsonObject[USERNAME];
}

void
User::setUsername(const QJsonValue &username) {
    _jsonObject[USERNAME] = username;
}

QJsonValue
User::getDiscriminator() const {
    return _jsonObject[DISCRIMINATOR];
}

void
User::User::setDiscriminator(const QJsonValue &discriminator) {
    _jsonObject[DISCRIMINATOR] = discriminator;
}

QJsonValue
User::getAvatar() const {
    return _jsonObject[AVATAR];
}

void
User::setAvatar(const QJsonValue &avatar) {
    _jsonObject[AVATAR] = avatar;
}

QJsonValue
User::getBot() const {
    return _jsonObject[BOT];
}

void
User::setBot(const QJsonValue &bot) {
    _jsonObject[BOT] = bot;
}

QJsonValue
User::getSystem() const {
    return _jsonObject[SYSTEM];
}

void
User::setSystem(const QJsonValue &system) {
    _jsonObject[SYSTEM] = system;
}

QJsonValue
User::getMfaEnabled() const {
    return _jsonObject[MFA_ENABLED];
}

void
User::setMfaEnabled(const QJsonValue &mfaEnabled) {
    _jsonObject[MFA_ENABLED] = mfaEnabled;
}

QJsonValue
User::getLocale() const {
    return _jsonObject[LOCALE];
}

void
User::setLocale(const QJsonValue &locale) {
    _jsonObject[LOCALE] = locale;
}

QJsonValue
User::getVerified() const {
    return _jsonObject[VERIFIED];
}

void
User::setVerified(const QJsonValue &verified) {
    _jsonObject[VERIFIED] = verified;
}

QJsonValue
User::getEmail() const {
    return _jsonObject[EMAIL];
}

void
User::setEmail(const QJsonValue &email) {
    _jsonObject[EMAIL] = email;
}

QJsonValue
User::getFlags() const {
    return _jsonObject[FLAGS];
}

void
User::setFlags(const QJsonValue &flags) {
    _jsonObject[FLAGS] = flags;
}

QJsonValue
User::getPremiumType() const {
    return _jsonObject[PREMIUM_TYPE];
}

void
User::setPremiumType(const QJsonValue &premiumType) {
    _jsonObject[PREMIUM_TYPE] = premiumType;
}

QJsonValue
User::getPublicFlags() const {
    return _jsonObject[PUBLIC_FLAGS];
}

void
User::setPublicFlags(const QJsonValue &publicFlags) {
    _jsonObject[PUBLIC_FLAGS] = publicFlags;
}
