#ifndef USER_H
#define USER_H

#include "jsonserializeable.h"


class User : public JsonSerializeable
{
    Q_OBJECT

public:
    const QString ID = "id";
    const QString USERNAME = "username";
    const QString DISCRIMINATOR = "discriminator";
    const QString AVATAR = "avatar";
    const QString BOT = "bot";
    const QString SYSTEM = "system";
    const QString MFA_ENABLED = "mfa_enabled";
    const QString LOCALE = "locale";
    const QString VERIFIED = "verified";
    const QString EMAIL = "email";
    const QString FLAGS = "flags";
    const QString PREMIUM_TYPE = "premium_type";
    const QString PUBLIC_FLAGS = "public_flags";

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;

    Q_PROPERTY(QString username READ getUsername WRITE setUsername)
    QString username;

    Q_PROPERTY(QString discriminator READ getDiscriminator WRITE setDiscriminator)
    QString discriminator;

    Q_PROPERTY(QString avatar READ getAvatar WRITE setAvatar)
    QString avatar;

    Q_PROPERTY(QJsonValue bot READ getBot WRITE setBot)
    QSharedPointer<bool> bot;

    Q_PROPERTY(QJsonValue system READ getSystem WRITE setSystem)
    QSharedPointer<bool> system;

    Q_PROPERTY(QJsonValue mfa_enabled READ getMfaEnabled WRITE setMfaEnabled)
    QSharedPointer<bool> mfa_enabled;

    Q_PROPERTY(QString locale READ getLocale WRITE setLocale)
    QString locale;

    Q_PROPERTY(QJsonValue verified READ getVerified WRITE setVerified)
    QSharedPointer<bool> verified;

    Q_PROPERTY(QString email READ getEmail WRITE setEmail)
    QString email;

    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
    QSharedPointer<int> flags;

    Q_PROPERTY(QJsonValue premium_type READ getPremiumType WRITE setPremiumType)
    QSharedPointer<int> premium_type;

    Q_PROPERTY(QJsonValue public_flags READ getPublicFlags WRITE setPublicFlags)
    QSharedPointer<int> public_flags;

    QString
    getId() {
        return id;
    }

    void
    setId(QString id) {
        this->id = id;
    }

    QString
    getUsername() {
        return username;
    }

    void
    setUsername(QString username) {
        this->username = username;
    }

    QString
    getDiscriminator() {
        return discriminator;
    }

    void
    setDiscriminator(QString discriminator) {
        this->discriminator = discriminator;
    }

    QString
    getAvatar() {
        return avatar;
    }

    void
    setAvatar(QString avatar) {
        this->avatar = avatar;
    }

    QJsonValue
    getBot() {
        if (bot) {
            return QJsonValue(*bot);
        } else {
            return QJsonValue();
        }
    }

    void
    setBot(QJsonValue bot) {
        if (!bot.isNull()) {
            this->bot = QSharedPointer<bool>(new bool(bot.toBool()));
        }
    }

    QJsonValue
    getSystem() {
        if (system) {
            return QJsonValue(*system);
        } else {
            return QJsonValue();
        }
    }

    void
    setSystem(QJsonValue system) {
        if (!system.isNull()) {
            this->system = QSharedPointer<bool>(new bool(system.toBool()));
        }
    }

    QJsonValue
    getMfaEnabled() {
        if (mfa_enabled) {
            return QJsonValue(*mfa_enabled);
        } else {
            return QJsonValue();
        }
    }

    void
    setMfaEnabled(QJsonValue mfa_enabled) {
        if (!mfa_enabled.isNull()) {
            this->mfa_enabled = QSharedPointer<bool>(new bool(mfa_enabled.toBool()));
        }
    }

    QString
    getLocale() {
        return locale;
    }

    void
    setLocale(QString locale) {
        this->locale = locale;
    }

    QJsonValue
    getVerified() {
        if (verified) {
            return QJsonValue(*verified);
        } else {
            return QJsonValue();
        }
    }

    void
    setVerified(QJsonValue verified) {
        if (!verified.isNull()) {
            this->verified = QSharedPointer<bool>(new bool(verified.toBool()));
        }
    }

    QString
    getEmail() {
        return email;
    }

    void
    setEmail(QString email) {
        this->email = email;
    }

    QJsonValue
    getFlags() {
        if (flags) {
            return QJsonValue(*flags);
        } else {
            return QJsonValue();
        }
    }

    void
    setFlags(QJsonValue flags) {
        if (!flags.isNull()) {
            this->flags = QSharedPointer<int>(new int(flags.toInt()));
        }
    }

    QJsonValue
    getPremiumType() {
        if (premium_type) {
            return QJsonValue(*premium_type);
        } else {
            return QJsonValue();
        }
    }

    void
    setPremiumType(QJsonValue premium_type) {
        if (!premium_type.isNull()) {
            this->premium_type = QSharedPointer<int>(new int(premium_type.toInt()));
        }
    }

    QJsonValue
    getPublicFlags() {
        if (public_flags) {
            return QJsonValue(*public_flags);
        } else {
            return QJsonValue();
        }
    }

    void
    setPublicFlags(QJsonValue public_flags) {
        if (!public_flags.isNull()) {
            this->public_flags = QSharedPointer<int>(new int(public_flags.toInt()));
        }
    }

    void read(const QJsonObject &jsonObject) override {
        JsonUtils::readFromJson(*this, jsonObject);
    }

    void write(QJsonObject &jsonObject) override {
        JsonUtils::writeToJson(*this, jsonObject);
    }
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
