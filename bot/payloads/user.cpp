#include "user.h"

#include "util/jsonutils.h"

QString
User::getId() {
    return id;
}

void
User::setId(QString id) {
    this->id = id;
}

QString
User::getUsername() {
    return username;
}

void
User::setUsername(QString username) {
    this->username = username;
}

QString
User::getDiscriminator() {
    return discriminator;
}

void
User::User::setDiscriminator(QString discriminator) {
    this->discriminator = discriminator;
}

QString
User::getAvatar() {
    return avatar;
}

void
User::setAvatar(QString avatar) {
    this->avatar = avatar;
}

QJsonValue
User::getBot() {
    if (bot) {
        return QJsonValue(*bot);
    } else {
        return QJsonValue();
    }
}

void
User::setBot(QJsonValue bot) {
    if (!bot.isNull()) {
        this->bot = QSharedPointer<bool>(new bool(bot.toBool()));
    }
}

QJsonValue
User::getSystem() {
    if (system) {
        return QJsonValue(*system);
    } else {
        return QJsonValue();
    }
}

void
User::setSystem(QJsonValue system) {
    if (!system.isNull()) {
        this->system = QSharedPointer<bool>(new bool(system.toBool()));
    }
}

QJsonValue
User::getMfaEnabled() {
    if (mfa_enabled) {
        return QJsonValue(*mfa_enabled);
    } else {
        return QJsonValue();
    }
}

void
User::setMfaEnabled(QJsonValue mfa_enabled) {
    if (!mfa_enabled.isNull()) {
        this->mfa_enabled = QSharedPointer<bool>(new bool(mfa_enabled.toBool()));
    }
}

QString
User::getLocale() {
    return locale;
}

void
User::setLocale(QString locale) {
    this->locale = locale;
}

QJsonValue
User::getVerified() {
    if (verified) {
        return QJsonValue(*verified);
    } else {
        return QJsonValue();
    }
}

void
User::setVerified(QJsonValue verified) {
    if (!verified.isNull()) {
        this->verified = QSharedPointer<bool>(new bool(verified.toBool()));
    }
}

QString
User::getEmail() {
    return email;
}

void
User::setEmail(QString email) {
    this->email = email;
}

QJsonValue
User::getFlags() {
    if (flags) {
        return QJsonValue(*flags);
    } else {
        return QJsonValue();
    }
}

void
User::setFlags(QJsonValue flags) {
    if (!flags.isNull()) {
        this->flags = QSharedPointer<int>(new int(flags.toInt()));
    }
}

QJsonValue
User::getPremiumType() {
    if (premium_type) {
        return QJsonValue(*premium_type);
    } else {
        return QJsonValue();
    }
}

void
User::setPremiumType(QJsonValue premium_type) {
    if (!premium_type.isNull()) {
        this->premium_type = QSharedPointer<int>(new int(premium_type.toInt()));
    }
}

QJsonValue
User::getPublicFlags() {
    if (public_flags) {
        return QJsonValue(*public_flags);
    } else {
        return QJsonValue();
    }
}

void
User::setPublicFlags(QJsonValue public_flags) {
    if (!public_flags.isNull()) {
        this->public_flags = QSharedPointer<int>(new int(public_flags.toInt()));
    }
}

void
User::read(const QJsonObject &jsonObject) {
    JsonUtils::readFromJson(*this, jsonObject);
}

void
User::write(QJsonObject &jsonObject) {
    JsonUtils::writeToJson(*this, jsonObject);
}
