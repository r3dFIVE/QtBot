#ifndef USER_H
#define USER_H

#include "jsonserializable.h"


class User : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ID;
    static const QString USERNAME;
    static const QString DISCRIMINATOR;
    static const QString AVATAR;
    static const QString BOT;
    static const QString SYSTEM;
    static const QString MFA_ENABLED;
    static const QString LOCALE;
    static const QString VERIFIED;
    static const QString EMAIL;
    static const QString FLAGS;
    static const QString PREMIUM_TYPE;
    static const QString PUBLIC_FLAGS;

    User() {}
    User(const QByteArray &json) : JsonSerializable(json) {}
    User(const QJsonObject &json) : JsonSerializable(json) {}
    User(const QString &json) : JsonSerializable(json) {}

    QJsonValue getAvatar() const;
    QJsonValue getBot() const;
    QJsonValue getDiscriminator() const;
    QJsonValue getEmail() const;
    QJsonValue getFlags() const;
    QJsonValue getId() const;
    QJsonValue getLocale() const;
    QJsonValue getMfaEnabled() const;
    QJsonValue getPremiumType() const;
    QJsonValue getPublicFlags() const;
    QJsonValue getSystem() const;
    QJsonValue getUsername() const;
    QJsonValue getVerified() const;
    void setAvatar(const QJsonValue &avatar);
    void setBot(const QJsonValue &bot);
    void setDiscriminator(const QJsonValue &discriminator);
    void setEmail(const QJsonValue &email);
    void setFlags(const QJsonValue &flags);
    void setId(const QJsonValue &id);
    void setLocale(const QJsonValue &locale);
    void setMfaEnabled(const QJsonValue &mfaEnabled);
    void setPremiumType(const QJsonValue &premiumType);
    void setPublicFlags(const QJsonValue &publicFlags);
    void setSystem(const QJsonValue &system);
    void setUsername(const QJsonValue &username);
    void setVerified(const QJsonValue &verified);

    Q_PROPERTY(QJsonValue id READ getId WRITE setId)
    Q_PROPERTY(QJsonValue username READ getUsername WRITE setUsername)
    Q_PROPERTY(QJsonValue discriminator READ getDiscriminator WRITE setDiscriminator)
    Q_PROPERTY(QJsonValue avatar READ getAvatar WRITE setAvatar)
    Q_PROPERTY(QJsonValue bot READ getBot WRITE setBot)
    Q_PROPERTY(QJsonValue system READ getSystem WRITE setSystem)
    Q_PROPERTY(QJsonValue mfa_enabled READ getMfaEnabled WRITE setMfaEnabled)
    Q_PROPERTY(QJsonValue locale READ getLocale WRITE setLocale)
    Q_PROPERTY(QJsonValue verified READ getVerified WRITE setVerified)
    Q_PROPERTY(QJsonValue email READ getEmail WRITE setEmail)
    Q_PROPERTY(QJsonValue flags READ getFlags WRITE setFlags)
    Q_PROPERTY(QJsonValue premium_type READ getPremiumType WRITE setPremiumType)
    Q_PROPERTY(QJsonValue public_flags READ getPublicFlags WRITE setPublicFlags)
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
